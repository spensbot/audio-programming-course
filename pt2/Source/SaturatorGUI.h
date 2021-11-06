/*
  ==============================================================================

    SaturatorGUI.h
    Created: 31 Oct 2021 10:57:38am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Saturator.h"

class SaturatorGUI : public juce::Component
{
public:
    SaturatorGUI(Saturator::State& state, std::function<void()> onChange): _state(state) {
        addAndMakeVisible(&_slider);
        _slider.setRange(1.f, 100.f);
        _slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _slider.onValueChange = [this, onChange]{ _state.saturation = _slider.getValue(); onChange(); };
        _slider.setValue(1.f);
        _slider.setSkewFactorFromMidPoint(10.f);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _slider.setBounds(bounds);
    }

private:
    Saturator::State& _state;
    juce::Slider _slider;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturatorGUI)
};
