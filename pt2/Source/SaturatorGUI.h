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
#include "TransferFunctionVisualizer.h"

class SaturatorGUI : public juce::Component
{
public:
    SaturatorGUI(Saturator::State& state, std::function<void()> onChange): _state(state), _transferFunctionVisualizer(_state) {
        addAndMakeVisible(&_slider);
        LabelledSlider::Options o{};
        o.min = 1.f;
        o.max = 100.f;
        o.onChange = [this, onChange] (float val) { _state.saturation = val; onChange(); _transferFunctionVisualizer.update(); };
        o.init = 1.f;
        o.skewMidpoint = 10.f;
        o.horizontal = true;
        _slider.setup(o);
        
        addAndMakeVisible(&_transferFunctionVisualizer);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _slider.setBounds(bounds.removeFromTop(30));
        bounds.reduce(10, 10);
        _transferFunctionVisualizer.setBounds(bounds);
    }

private:
    Saturator::State& _state;
    LabelledSlider _slider;
    TransferFunctionVisualizer _transferFunctionVisualizer;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturatorGUI)
};
