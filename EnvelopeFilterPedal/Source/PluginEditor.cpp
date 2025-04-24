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
    

    
    //Sensitivity
    auto sensitivityImage = juce::ImageCache::getFromMemory(BinaryData::sensitivity_sprite_png, BinaryData::sensitivity_sprite_pngSize);
    sensitivityKnobLAF = std::make_unique<CustomKnobLookAndFeel>(sensitivityImage, 125);
    sensitivity.setLookAndFeel(sensitivityKnobLAF.get());
    
    // MaxFreq
    auto maxfreqImage = juce::ImageCache::getFromMemory(BinaryData::maxfreq_sprite_png, BinaryData::maxfreq_sprite_pngSize);
    maxFreqKnobLAF = std::make_unique<CustomKnobLookAndFeel>(maxfreqImage, 125);
    maxFreq.setLookAndFeel(maxFreqKnobLAF.get());

    // MinFreq
    auto minfreqImage = juce::ImageCache::getFromMemory(BinaryData::minfreq_sprite_png, BinaryData::minfreq_sprite_pngSize);
    minFreqKnobLAF = std::make_unique<CustomKnobLookAndFeel>(minfreqImage, 125);
    minFreq.setLookAndFeel(minFreqKnobLAF.get());

    // Resonance
    auto resonanceImage = juce::ImageCache::getFromMemory(BinaryData::resonance_sprite_png, BinaryData::resonance_sprite_pngSize);
    resonanceKnobLAF = std::make_unique<CustomKnobLookAndFeel>(resonanceImage, 125);
    resonance.setLookAndFeel(resonanceKnobLAF.get());
    
    
  
    bypassButton.setBounds(113, 25, 250, 250);    //bypassButton.setButtonText("Bypass");
    bypassButton.onClick = [this]() {
        audioProcessor.bypassButtonClicked(bypassButton.getToggleState());
    };
    bypassButton.setToggleState(audioProcessor.BYPASSED_DEFAULT, juce::dontSendNotification); // set the initial state "on"
    addAndMakeVisible(bypassButton); // include this on the plugin window
    

    sweepDirection.setBounds(236, 25, 250, 250);
   //sweepDirection.setButtonText("Sweep Direction");
    //sweepDirection.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(sweepDirection); // include this on the plugin window
    

    filterType.setBounds(175, 255, 250, 250);
   // filterType.setButtonText("FilterType");
   //filterType.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(filterType); // include this on the plugin window
    
  
    //sensitivity.setBounds(400 - 50, 630 - 50, 100, 100); // (350, 580, 100, 100)
    sensitivity.setBounds(175, 505, 250, 250);
    sensitivity.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sensitivity.setRange(-18.f, 6.f, .1f);
    sensitivity.onValueChange = [this](){
        audioProcessor.sensitivitySliderChanged(sensitivity.getValue());
    };
    sensitivity.setValue(audioProcessor.SENSITIVITY_DEFAULT);
    sensitivity.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(sensitivity);
    
    

    minFreq.setBounds(50, 420, 250, 250);
    minFreq.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    minFreq.setRange(-18.f, 6.f, .1f);
    minFreq.onValueChange = [this](){
        audioProcessor.minFreqSliderChanged(minFreq.getValue());
    };
    minFreq.setValue(audioProcessor.MIN_DEFAULT);
    minFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(minFreq);

    
    maxFreq.setBounds(300, 420, 250, 250);
    maxFreq.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    maxFreq.setRange(-18.f, 6.f, .1f);
    maxFreq.onValueChange = [this](){
        audioProcessor.maxFreqSliderChanged(maxFreq.getValue());
    };
    maxFreq.setValue(audioProcessor.MAX_DEFAULT);
    maxFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(maxFreq);
    
    
    resonance.setBounds(175, 345, 250, 250);
    resonance.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonance.setRange(-18.f, 6.f, .1f);
    resonance.onValueChange = [this](){
        audioProcessor.resonanceSliderChanged(resonance.getValue());
    };
    resonance.setValue(audioProcessor.RESONANCE_DEFAULT);
    resonance.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
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

