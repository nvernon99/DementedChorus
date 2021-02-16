/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
    AUTHOR: Nolan Vernon
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DementedChorusAudioProcessorEditor::DementedChorusAudioProcessorEditor (DementedChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 600);

    //Attachments
    depth1Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DEPTH1", depth1Slider);
    rate1Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RATE1", rate1Slider);
    feedback1Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "FEEDBACK1", feedback1Slider);
    delay1Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DELAY1", delay1Slider);
    mix1Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "MIX1", mix1Slider);

    depth2Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DEPTH2", depth2Slider);
    rate2Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RATE2", rate2Slider);
    feedback2Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "FEEDBACK2", feedback2Slider);
    delay2Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DELAY2", delay2Slider);
    mix2Attachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "MIX2", mix2Slider);

    //styles
    depth1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rate1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedback1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delay1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mix1Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);

    depth2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rate2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedback2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delay2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mix2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);

    depth1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    rate1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    feedback1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    delay1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mix1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    depth2Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    rate2Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    feedback2Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    delay2Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mix2Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);



    addAndMakeVisible(depth1Slider);
    addAndMakeVisible(rate1Slider);
    addAndMakeVisible(feedback1Slider);
    addAndMakeVisible(delay1Slider);
    addAndMakeVisible(mix1Slider);

    addAndMakeVisible(depth2Slider);
    addAndMakeVisible(rate2Slider);
    addAndMakeVisible(feedback2Slider);
    addAndMakeVisible(delay2Slider);
    addAndMakeVisible(mix2Slider);

    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::darkslategrey);

}

DementedChorusAudioProcessorEditor::~DementedChorusAudioProcessorEditor()
{
}

//==============================================================================
void DementedChorusAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::lightseagreen);


    g.setColour (juce::Colours::darkslategrey);
    g.drawRoundedRectangle(5.0f, 95.0f, 90.0f, 500.0f, 10.0f, 3.0f);
    g.drawRoundedRectangle(105.0f, 95.0f, 90.0f, 500.0f, 10.0f, 3.0f);
    
    g.setFont(25.0f);
    g.drawSingleLineText("I", 50, 80, juce::Justification::centred);
    g.drawSingleLineText("II", 150, 80, juce::Justification::centred);

    g.setFont (15.0f);
    g.drawSingleLineText("DEPTH", 50, 190, juce::Justification::centred);
    g.drawSingleLineText("DEPTH", 150, 190, juce::Justification::centred);
    g.drawSingleLineText("RATE", 50, 290, juce::Justification::centred);
    g.drawSingleLineText("RATE", 150, 290, juce::Justification::centred);
    g.drawSingleLineText("FEEDBACK", 50, 390, juce::Justification::centred);
    g.drawSingleLineText("FEEDBACK", 150, 390, juce::Justification::centred);
    g.drawSingleLineText("DELAY", 50, 490, juce::Justification::centred);
    g.drawSingleLineText("DELAY", 150, 490, juce::Justification::centred);
    g.drawSingleLineText("DRY/WET", 50, 590, juce::Justification::centred);
    g.drawSingleLineText("DRY/WET", 150, 590, juce::Justification::centred);
}

void DementedChorusAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    depth1Slider.setBounds(10, 100, 80, 80);
    rate1Slider.setBounds(10, 200, 80, 80);
    feedback1Slider.setBounds(10, 300, 80, 80);
    delay1Slider.setBounds(10, 400, 80, 80);
    mix1Slider.setBounds(10, 500, 80, 80);

    depth2Slider.setBounds(110, 100, 80, 80);
    rate2Slider.setBounds(110, 200, 80, 80);
    feedback2Slider.setBounds(110, 300, 80, 80);
    delay2Slider.setBounds(110, 400, 80, 80);
    mix2Slider.setBounds(110, 500, 80, 80);
}
