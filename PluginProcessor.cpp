/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.
    AUTHOR: Nolan Vernon
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DementedChorusAudioProcessor::DementedChorusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", DementedChorusAudioProcessor::createParams())
#endif
{
}

DementedChorusAudioProcessor::~DementedChorusAudioProcessor()
{
}

//==============================================================================
const juce::String DementedChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DementedChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DementedChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DementedChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DementedChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DementedChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DementedChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DementedChorusAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DementedChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void DementedChorusAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DementedChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    chorus1.prepare(spec);
    chorus2.prepare(spec);
    gain.prepare(spec);


}

void DementedChorusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DementedChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DementedChorusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    /*
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }*/
    chorus1.setDepth(*apvts.getRawParameterValue("DEPTH1"));
    chorus1.setRate(*apvts.getRawParameterValue("RATE1"));
    chorus1.setFeedback(*apvts.getRawParameterValue("FEEDBACK1"));
    chorus1.setCentreDelay(*apvts.getRawParameterValue("DELAY1"));
    chorus1.setMix(*apvts.getRawParameterValue("MIX1"));

    chorus2.setDepth(*apvts.getRawParameterValue("DEPTH2"));
    chorus2.setRate(*apvts.getRawParameterValue("RATE2"));
    chorus2.setFeedback(*apvts.getRawParameterValue("FEEDBACK2"));
    chorus2.setCentreDelay(*apvts.getRawParameterValue("DELAY2"));
    chorus2.setMix(*apvts.getRawParameterValue("MIX2"));
    
    auto audioBlock = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    auto context2 = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    chorus1.process(context);
    chorus2.process(context);
    //gain.process(context);
    //gain.process(context2);


}

//==============================================================================
bool DementedChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DementedChorusAudioProcessor::createEditor()
{
    return new DementedChorusAudioProcessorEditor (*this);
}
void DementedChorusAudioProcessor::reset() {
    chorus1.reset();
    chorus2.reset();
    gain.reset();
}
//==============================================================================
void DementedChorusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DementedChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DementedChorusAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout DementedChorusAudioProcessor::createParams()
{
    //fxChain.setParameters(verbParams);

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DEPTH1", "Depth1", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.4f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RATE1", "Rate1", juce::NormalisableRange<float> { 0.1f, 8.0f, }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK1", "Feedback1", juce::NormalisableRange<float> { -1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DELAY1", "Delay1", juce::NormalisableRange<float> { 1.0f, 99.0f, }, 7.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MIX1", "Mix1", juce::NormalisableRange<float> { 0.0f, 1.0f, }, 0.4f));


    params.push_back(std::make_unique<juce::AudioParameterFloat>("DEPTH2", "Depth2", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.4f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RATE2", "Rate2", juce::NormalisableRange<float> { 0.1f, 8.0f, }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK2", "Feedback2", juce::NormalisableRange<float> { -1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DELAY2", "Delay2", juce::NormalisableRange<float> { 1.0f, 99.0f, }, 7.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MIX2", "Mix2", juce::NormalisableRange<float> { 0.0f, 1.0f, }, 0.4f));

    return { params.begin(), params.end() };
}
