/*
  ==============================================================================

    EnvelopeFollower.h
    Created: 27 Feb 2025 7:07:42pm
    Author:  Jakobi Braden

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class EnvelopeFollower{
    
public:
    
    float ProcessRectification(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples);
    float calculateRMS(float inputSignal);
    
    
    
    
private:
    
    juce::AudioParameterBool useRMS; // Determines the envelope smoothing type (RMS or Rectification)
    juce::AudioParameterFloat rmsValue;
    juce::AudioParameterFloat smoothingFactor;
    
    juce::AudioParameterFloat attackTime; // Determines the attack
    juce::AudioParameterFloat decayTime; // Determines envelope decay
    juce::AudioParameterFloat envelopeValue;
    
    
};

