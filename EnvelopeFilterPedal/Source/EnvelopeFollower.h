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
    
    float calculateRMS(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples);
     
    float calculatePeak(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples, float alpha);
    
    
private:

    float smoothedPeak = 0.0f;
    float alpha = 0.3f;
    float rms = 0.0f;

};

 
