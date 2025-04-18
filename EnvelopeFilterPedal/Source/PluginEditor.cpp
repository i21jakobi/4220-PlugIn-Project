/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EnvelopeFilterPedalAudioProcessorEditor::EnvelopeFilterPedalAudioProcessorEditor (EnvelopeFilterPedalAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (refWidth, refHeight);
    
  
    bypassButton.setBounds(20.f, 20.f, 80.f, 30.f); // x , y, width, height
    bypassButton.setButtonText("Bypass");
    bypassButton.onClick = [this]() {
        audioProcessor.bypassButtonClicked(bypassButton.getToggleState());
    };
    bypassButton.setToggleState(audioProcessor.BYPASSED_DEFAULT, juce::dontSendNotification); // set the initial state "on"
    addAndMakeVisible(bypassButton); // include this on the plugin window
    

    sweepDirection.setBounds(135.f, 20.f, 80.f, 30.f); // x , y, width, height
    sweepDirection.setButtonText("Sweep Direction");
    //sweepDirection.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(sweepDirection); // include this on the plugin window
    

    filterType.setBounds(250.f, 20.f, 80.f, 30.f); // x , y, width, height
    filterType.setButtonText("FilterType");
   //filterType.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(filterType); // include this on the plugin window
    
  
    sensitivity.setBounds(125.f, 380.f, 100.f, 100.f);
    sensitivity.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sensitivity.setRange(-18.f, 6.f, .1f);
    sensitivity.onValueChange = [this](){
        audioProcessor.sensitivitySliderChanged(sensitivity.getValue());
    };
    sensitivity.setValue(audioProcessor.SENSITIVITY_DEFAULT);
    sensitivity.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(sensitivity);
    
    

    minFreq.setBounds(20.f, 380.f, 80.f, 80.f);
    minFreq.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    minFreq.setRange(-18.f, 6.f, .1f);
    minFreq.onValueChange = [this](){
        audioProcessor.minFreqSliderChanged(minFreq.getValue());
    };
    minFreq.setValue(audioProcessor.MIN_DEFAULT);
    minFreq.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(minFreq);

    
    maxFreq.setBounds(250.f, 380.f, 80.f, 80.f);
    maxFreq.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    maxFreq.setRange(-18.f, 6.f, .1f);
    maxFreq.onValueChange = [this](){
        audioProcessor.maxFreqSliderChanged(maxFreq.getValue());
    };
    maxFreq.setValue(audioProcessor.MAX_DEFAULT);
    maxFreq.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(maxFreq);
    
    
    resonance.setBounds(135.f, 290.f, 80.f, 80.f);
    resonance.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonance.setRange(-18.f, 6.f, .1f);
    resonance.onValueChange = [this](){
        audioProcessor.resonanceSliderChanged(resonance.getValue());
    };
    resonance.setValue(audioProcessor.RESONANCE_DEFAULT);
    resonance.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(resonance);
    
    
    // APVTS TEMPLATE
    sliderAttachments.emplace_back(std::make_unique<SliderAttachment> 
                                   (audioProcessor.apvts, "Sensitivity", sensitivity));
    sliderAttachments.emplace_back(std::make_unique<SliderAttachment>
                                   (audioProcessor.apvts, "MaxFreqKnob", maxFreq));
    sliderAttachments.emplace_back(std::make_unique<SliderAttachment>
                                   (audioProcessor.apvts, "MinFreqKnob", minFreq));
    sliderAttachments.emplace_back(std::make_unique<SliderAttachment>
                                   (audioProcessor.apvts, "ResonanceKnob", resonance));
    
    
    buttonAttachments.emplace_back(std::make_unique<ButtonAttachment> (audioProcessor.apvts, "BypassButton", bypassButton));
    buttonAttachments.emplace_back(std::make_unique<ButtonAttachment> (audioProcessor.apvts, "SweepDirection", sweepDirection));
    buttonAttachments.emplace_back(std::make_unique<ButtonAttachment> (audioProcessor.apvts, "FilterType", filterType));


    
   
}

EnvelopeFilterPedalAudioProcessorEditor::~EnvelopeFilterPedalAudioProcessorEditor()
{
}

//==============================================================================
void EnvelopeFilterPedalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EnvelopeFilterPedalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

