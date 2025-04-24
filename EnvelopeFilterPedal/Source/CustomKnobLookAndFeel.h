/*
  ==============================================================================

    CustomKnobLookAndFeel.h
    Created: 24 Apr 2025 12:52:52pm
    Author:  Jakobi Braden

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomKnobLookAndFeel : public juce::LookAndFeel_V4 {
public:
    CustomKnobLookAndFeel(const juce::Image& knobImage, int numFrames)
        : knobStrip(knobImage), frameCount(numFrames) {}

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider& slider) override
    {
        if (knobStrip.isValid()) {
            const int frame = std::clamp(static_cast<int>(sliderPosProportional * frameCount), 0, frameCount - 1);
            const int frameHeight = knobStrip.getHeight() / frameCount;
            const int frameWidth = knobStrip.getWidth();

            g.drawImage(knobStrip,
                        x, y, width, height,
                        0, frame * frameHeight, frameWidth, frameHeight);
        } else {
            // fallback if image fails
            juce::LookAndFeel_V4::drawRotarySlider(g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
        }
    }

private:
    juce::Image knobStrip;
    int frameCount = 125;
};

