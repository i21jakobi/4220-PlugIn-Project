/*
  ==============================================================================

    EnvelopeFollower.cpp
    Created: 27 Feb 2025 7:07:42pm
    Author:  Jakobi Braden

  ==============================================================================
*/

#include "EnvelopeFollower.h"



    float EnvelopeFollower::calculateRMS (juce::AudioBuffer<float> & buffer, const int channel, const int numSamples){
        
        float sumSquares = 0.0f;
        
        for (int i = 0; i < numSamples; ++i){
            sumSquares += buffer.getSample(channel, i) * buffer.getSample(channel, i);
        }
        
        rms = std::sqrt(sumSquares/numSamples); // Compute RMS value
        
        if (numSamples <= 0) return 0.0f;
        
        return rms;
    }
    
    
    float EnvelopeFollower::calculatePeak(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples, float alpha){
        
//        float peak = 0.f;
//        float smoothedPeak = 0.f;

        for (int i = 0; i < numSamples; ++i){
        float absSample = std::abs(buffer.getSample(channel, i)); // Get absolute value
        smoothedPeak = (alpha * absSample) + (1.0f - alpha) * smoothedPeak;
    }

        return smoothedPeak;
     
}

    
