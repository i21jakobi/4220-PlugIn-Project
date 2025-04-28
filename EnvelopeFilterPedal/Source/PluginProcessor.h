/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Biquad.h"
#include "EnvelopeFollower.h"
#include "ParameterTypes.h"


//==============================================================================
/**
*/
class EnvelopeFilterPedalAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    EnvelopeFilterPedalAudioProcessor();
    ~EnvelopeFilterPedalAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    static constexpr bool BYPASSED_DEFAULT = false;
    
    static constexpr float FREQ_DEFAULT = 1000.f;

    float freqValue = FREQ_DEFAULT;

    static constexpr float FILTER_AMP_DEFAULT = 0.f;

    float filterAmpValue = FILTER_AMP_DEFAULT;

    static constexpr float RESONANCE_DEFAULT = 0.7071f;

    float resonance = RESONANCE_DEFAULT;

    static constexpr float MIN_DEFAULT = 200.f;
    
    float minFreq = MIN_DEFAULT;
    
    static constexpr float MAX_DEFAULT = 10000.f;;
    
    float maxFreq = MAX_DEFAULT;
    
    static constexpr float ALPHA_DEFAULT = 0.3f;
    
    float peakAlpha = ALPHA_DEFAULT;
    
    static constexpr float SENSITIVITY_DEFAULT = 1.f;
    
    float sensitivity = SENSITIVITY_DEFAULT;
    
    float cutoffFreq;
    
    float envelopeValue;
    
   

    
    Biquad::FilterType filterType = Biquad::FilterType::LPF;
    
    
    juce::AudioProcessorValueTreeState apvts;
    
    void sensitivitySliderChanged(float value){
        sensitivitySliderValue.store(value);
    }
    
    void resonanceSliderChanged(float value){
        resonanceSliderValue.store(value);
    }
    
    void maxFreqSliderChanged(float value){
        maxFreqSliderValue.store(value);
    }
    
    void minFreqSliderChanged(float value){
        minFreqSliderValue.store(value);
    }
    
    
    void bypassButtonClicked(bool isByp){
        isBypassed.store(isByp);
    }
   
    
    
private:
    
    Biquad filter {Biquad::FilterType::LPF,0.7071f};

    EnvelopeFollower envelope; 
    
    float smoothedCutoff[2] = {0.f};
    
    std::atomic<float> sensitivitySliderValue = SENSITIVITY_DEFAULT;
    std::atomic<float> resonanceSliderValue = RESONANCE_DEFAULT;
    std::atomic<float> maxFreqSliderValue = MAX_DEFAULT;
    std::atomic<float> minFreqSliderValue = MIN_DEFAULT;
    
    std::atomic<bool> isBypassed = BYPASSED_DEFAULT;
    
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeFilterPedalAudioProcessor)
};
