/*
  ==============================================================================

    VisualizerCursor.h
    Created: 13 Nov 2021 10:32:07pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VisualizerState.h"

//==============================================================================
/*
*/
class VisualizerCursor : public juce::Component, public juce::Timer
{
public:
    VisualizerCursor(float& generator_t, VisualizerState& state)
    : _generator_t(generator_t)
    , _state(state)
    {
        startTimerHz(60.0);
    }

    ~VisualizerCursor() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        g.setColour (juce::Colour::fromHSV(0.0f,1.0f,1.0f,1.0f));
        const auto x = _generator_t / _state.windowSeconds * getWidth();
        g.drawLine(x, 0.0, x, getHeight(), 2.0);
    }
    
    void timerCallback() override {
        if (_generator_t < _state.windowSeconds)
            repaint();
    }
    
private:
    float& _generator_t;
    VisualizerState& _state;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualizerCursor)
};
