/*
  ==============================================================================

    LevelGUI.h
    Created: 31 Oct 2021 10:57:23am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Level.h"
#include "LabelledSlider.h"

class LevelGUI : public juce::Component
{
public:
    LevelGUI(Level::State& state, std::function<void()> onChange): _state(state) {
        addAndMakeVisible(&_slider);
        
        LabelledSlider::Options o{};
        o.onChange = [this, onChange] (float val) { _state.level = val; onChange(); };
        o.init = 1.f;
        
        _slider.setup(o);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _slider.setBounds(bounds);
    }

private:
    LabelledSlider _slider;
    Level::State& _state;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelGUI)
};

