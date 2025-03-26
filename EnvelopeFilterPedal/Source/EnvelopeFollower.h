/*
  ==============================================================================

    EnvelopeFollower.h
    Created: 27 Feb 2025 7:07:42pm
    Author:  Jakobi Braden

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Biquad.h"

class EnvelopeFollower{
    
public:
    
    void calculateRMS(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples);
     
    void calculatePeak(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples, float alpha);
    
    void smoothEnvelope();
    
    
    
    
private:

    float smoothedPeak = 0.0f;
    float alpha = 0.3f;
    float rms = 0.0f;

};

