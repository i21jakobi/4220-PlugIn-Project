/*
  ==============================================================================

    FilterProcessor.h
    Created: 27 Feb 2025 7:07:59pm
    Author:  Jakobi Braden

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class FilterProcessor{
    
public:
    
private:
    std::string filterType;
    juce::AudioParameterFloat filterResonance;
    juce::AudioParameterFloat baseCutoff;
    juce::AudioParameterFloat sensitivity;
    juce::AudioParameterBool sweepDirection;
    
};
