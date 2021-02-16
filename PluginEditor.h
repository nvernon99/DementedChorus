/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
    AUTHOR: Nolan Vernon
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DementedChorusAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DementedChorusAudioProcessorEditor (DementedChorusAudioProcessor&);
    ~DementedChorusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DementedChorusAudioProcessor& audioProcessor;

    //Sliders
    juce::Slider depth1Slider;
    juce::Slider rate1Slider;
    juce::Slider feedback1Slider;
    juce::Slider delay1Slider;
    juce::Slider mix1Slider;

    juce::Slider depth2Slider;
    juce::Slider rate2Slider;
    juce::Slider feedback2Slider;
    juce::Slider delay2Slider;
    juce::Slider mix2Slider;

    //attachments
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;


    std::unique_ptr<SliderAttachment> depth1Attachment;
    std::unique_ptr<SliderAttachment> rate1Attachment;
    std::unique_ptr<SliderAttachment> feedback1Attachment;
    std::unique_ptr<SliderAttachment> delay1Attachment;
    std::unique_ptr<SliderAttachment> mix1Attachment;

    std::unique_ptr<SliderAttachment> depth2Attachment;
    std::unique_ptr<SliderAttachment> rate2Attachment;
    std::unique_ptr<SliderAttachment> feedback2Attachment;
    std::unique_ptr<SliderAttachment> delay2Attachment;
    std::unique_ptr<SliderAttachment> mix2Attachment;

    //labels
    juce::Label depth1Label;
    juce::Label rate1Label;
    juce::Label feedback1Label;
    juce::Label delay1Label;
    juce::Label mix1Label;

    juce::Label depth2Label;
    juce::Label rate2Label;
    juce::Label feedback2Label;
    juce::Label delay2Label;
    juce::Label mix2Label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DementedChorusAudioProcessorEditor)
};
