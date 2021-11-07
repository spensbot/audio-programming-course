/*
  ==============================================================================

    SaturatorGUI.h
    Created: 31 Oct 2021 10:57:38am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Saturator.h"
#include "LabelledSlider.h"

class SaturatorGUI : public juce::Component
{
public:
    SaturatorGUI(Saturator::State& state, std::function<void()> onChange): _state(state) {
        addAndMakeVisible(&_slider);
        
        LabelledSlider::Options o{};
        o.min = 1.f;
        o.max = 100.f;
        o.onChange = [this, onChange] (float val) { _state.saturation = val; onChange(); };
        o.init = 1.f;
        o.skewMidpoint = 10.f;
//        o.label = "";
//        o.suffix = "";
        
        _slider.setup(o);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _slider.setBounds(bounds);
    }

private:
    Saturator::State& _state;
    LabelledSlider _slider;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturatorGUI)
};
