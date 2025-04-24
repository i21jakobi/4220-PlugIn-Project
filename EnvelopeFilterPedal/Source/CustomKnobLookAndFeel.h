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
                          float sliderPosProportional, float /*rotaryStartAngle*/,
                          float /*rotaryEndAngle*/, juce::Slider& slider) override
    {
        if (knobStrip.isValid()) {
            int frameIndex = std::clamp((int)std::round(sliderPosProportional * (frameCount - 1)), 0, frameCount - 1);
            int frameHeight = knobStrip.getHeight() / frameCount;
            int frameWidth = knobStrip.getWidth();

            g.drawImage(knobStrip,
                        x, y, width, height,
                        0, frameIndex * frameHeight, frameWidth, frameHeight);
        }
    }



    
    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button, bool /*highlighted*/, bool /*down*/) override
    {
        const int frame = button.getToggleState() ? 1 : 0;
        const int frameHeight = knobStrip.getHeight() / frameCount;
        const int frameWidth = knobStrip.getWidth();

        g.drawImage(knobStrip,
                    0, 0, button.getWidth(), button.getHeight(),
                    0, frame * frameHeight, frameWidth, frameHeight);
    }

private:
    juce::Image knobStrip;
    int frameCount = 125;
};

