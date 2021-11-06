/*
  ==============================================================================

    LevelGUI.h
    Created: 31 Oct 2021 10:57:23am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Level.h"

class LevelGUI : public juce::Component
{
public:
    LevelGUI(Level::State& state, std::function<void()> onChange): _state(state) {
        addAndMakeVisible(&_slider);
        _slider.setRange(0.f, 1.f);
        _slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _slider.onValueChange = [this, onChange]{
            _state.level = _slider.getValue();
            onChange();
        };
        _slider.setValue(1.0f);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _slider.setBounds(bounds);
    }

private:
    juce::Slider _slider;
    Level::State& _state;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelGUI)
};

