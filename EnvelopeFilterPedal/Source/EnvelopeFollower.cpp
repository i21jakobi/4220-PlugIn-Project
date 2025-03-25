/*
  ==============================================================================

    EnvelopeFollower.cpp
    Created: 27 Feb 2025 7:07:42pm
    Author:  Jakobi Braden

  ==============================================================================
*/

#include "EnvelopeFollower.h"

    
    float calculateRMS (juce::AudioBuffer<float> & buffer, const int channel, const int numSamples){
        
        float sumSquares = 0.0f;
        
        for (int i = 0; i < numSamples; ++i){
            sumSquares += buffer.getSample(channel, i) * buffer.getSample(channel, i);
        }
        
        return std::sqrt(sumSquares/numSamples); // Compute RMS value
        
    }
    
    
    float calculatePeak(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples){
        
        float peak = 0.0f;

        for (int i = 0; i < numSamples; ++i)
                {
        float absSample = std::abs(buffer.getSample(channel, i)); // Get absolute value
        if (absSample > peak)
            peak = absSample;
    }

    return peak; // Return the peak value
}
 
    
