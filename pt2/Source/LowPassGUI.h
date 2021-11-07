/*
  ==============================================================================

    LowPassGui.h
    Created: 31 Oct 2021 10:57:32am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "LowPass.h"
#include "LabelledSlider.h"

class LowPassGUI : public juce::Component
{
public:
    LowPassGUI(LowPass::State& state, std::function<void()> onChange): _state(state) {
        addAndMakeVisible(&_slider);
        
        LabelledSlider::Options o{};
        o.min = 20.f;
        o.max = 20000.f;
        o.onChange = [this, onChange] (float val) { _state.frequency = val; onChange(); };
        o.init = 20000.f;
        o.skewMidpoint = 500.f;
//        o.label = "";
        o.suffix = "Hz";
        
        _slider.setup(o);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _slider.setBounds(bounds);
    }

private:
    LowPass::State& _state;
    LabelledSlider _slider;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowPassGUI)
};
