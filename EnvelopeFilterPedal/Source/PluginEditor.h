/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomKnobLookAndFeel.h"


//==============================================================================
/**
*/
class EnvelopeFilterPedalAudioProcessorEditor  : public juce::AudioProcessorEditor
//                                                 public juce::Button::Listener,
//                                                 public juce::Slider::Listener
{
public:
    EnvelopeFilterPedalAudioProcessorEditor (EnvelopeFilterPedalAudioProcessor&);
    ~EnvelopeFilterPedalAudioProcessorEditor() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
//    void buttonClicked (juce::Button*) override; // provide implementation for pure virtual function
//    
//    void sliderValueChanged (juce::Slider *) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EnvelopeFilterPedalAudioProcessor& audioProcessor;
    
    juce::ToggleButton bypassButton;
    
    juce::ToggleButton sweepDirection;
    
    
    juce::Slider filterType;
    
    juce::Slider sensitivity;
    
    juce::Slider minFreq;
    
    juce::Slider maxFreq;
    
    juce::Slider resonance;
    
    
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;
    
    std::unique_ptr<CustomKnobLookAndFeel> sensitivityKnobLAF;
    std::unique_ptr<CustomKnobLookAndFeel> maxFreqKnobLAF;
    std::unique_ptr<CustomKnobLookAndFeel> minFreqKnobLAF;
    std::unique_ptr<CustomKnobLookAndFeel> resonanceKnobLAF;

    
    float refWidth = 600.f;
    float refHeight = 800.f;
    
    juce::Image backgroundImage;
  

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeFilterPedalAudioProcessorEditor)
};

