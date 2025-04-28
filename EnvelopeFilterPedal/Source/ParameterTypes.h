/*
  ==============================================================================

    ParameterTypes.h
    Created: 28 Apr 2025 11:47:16am
    Author:  Jakobi Braden

  ==============================================================================
*/

#pragma once

enum class FilterMode : int {LPF = 0, BPF = 1, HPF = 2};

struct PresetParams
{
    float sensitivity = 1.f;
    float minFreq = 200.f;
    float maxFreq = 10000.f;
    float resonance = 0.7071f;
    bool bypass = false;
    bool sweepUp = true;
    FilterMode mode = FilterMode::LPF;
}
