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
    
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::pedalBody_0001_png, BinaryData::pedalBody_0001_pngSize);
    
  
    bypassButton.setBounds(338 - 40, 150 - 15, 80, 30); // (298, 135, 80, 30)
    bypassButton.setButtonText("Bypass");
    bypassButton.onClick = [this]() {
        audioProcessor.bypassButtonClicked(bypassButton.getToggleState());
    };
    bypassButton.setToggleState(audioProcessor.BYPASSED_DEFAULT, juce::dontSendNotification); // set the initial state "on"
    addAndMakeVisible(bypassButton); // include this on the plugin window
    

    sweepDirection.setBounds(461 - 40, 150 - 15, 80, 30); // (421, 135, 80, 30)
    sweepDirection.setButtonText("Sweep Direction");
    //sweepDirection.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(sweepDirection); // include this on the plugin window
    

    filterType.setBounds(400 - 40, 380 - 15, 80, 30); // (360, 365, 80, 30)
    filterType.setButtonText("FilterType");
   //filterType.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(filterType); // include this on the plugin window
    
  
    sensitivity.setBounds(400 - 50, 630 - 50, 100, 100); // (350, 580, 100, 100)
    sensitivity.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sensitivity.setRange(-18.f, 6.f, .1f);
    sensitivity.onValueChange = [this](){
        audioProcessor.sensitivitySliderChanged(sensitivity.getValue());
    };
    sensitivity.setValue(audioProcessor.SENSITIVITY_DEFAULT);
    sensitivity.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(sensitivity);
    
    

    minFreq.setBounds(275 - 50, 550 - 50, 100, 100); // (225, 500, 100, 100)
    minFreq.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    minFreq.setRange(-18.f, 6.f, .1f);
    minFreq.onValueChange = [this](){
        audioProcessor.minFreqSliderChanged(minFreq.getValue());
    };
    minFreq.setValue(audioProcessor.MIN_DEFAULT);
    minFreq.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(minFreq);

    
    maxFreq.setBounds(525 - 50, 550 - 50, 100, 100); // (475, 500, 100, 100)
    maxFreq.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    maxFreq.setRange(-18.f, 6.f, .1f);
    maxFreq.onValueChange = [this](){
        audioProcessor.maxFreqSliderChanged(maxFreq.getValue());
    };
    maxFreq.setValue(audioProcessor.MAX_DEFAULT);
    maxFreq.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(maxFreq);
    
    
    resonance.setBounds(400 - 50, 475 - 50, 100, 100); // (350, 425, 100, 100)
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
    
    g.drawImage(backgroundImage, getLocalBounds().toFloat());

   
    g.setFont (juce::FontOptions (15.0f));

}

void EnvelopeFilterPedalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

