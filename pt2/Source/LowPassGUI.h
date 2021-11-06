/*
  ==============================================================================

    LowPassGui.h
    Created: 31 Oct 2021 10:57:32am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "LowPass.h"

class LowPassGUI : public juce::Component
{
public:
    LowPassGUI(LowPass::State& state, std::function<void()> onChange): _state(state) {
        addAndMakeVisible(&_label);
        addAndMakeVisible(&_slider);
        _slider.setRange(20.f, 20000.f);
        _slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
        _slider.onValueChange = [this, onChange]{ _state.frequency = _slider.getValue(); onChange(); };
        _slider.setValue(20000.f);
        _slider.setSkewFactorFromMidPoint(500.f);
        _slider.setTextValueSuffix("Hz");
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _slider.setBounds(bounds);
    }

private:
    LowPass::State& _state;
    juce::Label _label;
    juce::Slider _slider;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowPassGUI)
};
