/*
  ==============================================================================

    DelayGUI.h
    Created: 31 Oct 2021 10:57:13am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Delay.h"

class DelayGUI : public juce::Component
{
public:
    DelayGUI(Delay::State& state, std::function<void()> onChange): _state(state) {
        
        addAndMakeVisible(_delaySamples);
        _delaySamples.setRange(0.f, 1.f);
        _delaySamples.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _delaySamples.onValueChange = [this, onChange]{ _state.delaySeconds = _delaySamples.getValue(); onChange(); };
        _delaySamples.setValue(0.5f);
        
        addAndMakeVisible(_feedback);
        _feedback.setRange(0.f, 1.f);
        _feedback.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _feedback.onValueChange = [this, onChange]{ _state.feedback = _feedback.getValue(); onChange(); };
        _feedback.setValue(0.5f);
        
        addAndMakeVisible(_dry);
        _dry.setRange(0.f, 1.f);
        _dry.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _dry.onValueChange = [this, onChange]{ _state.dryMix = _dry.getValue(); onChange(); };
        _dry.setValue(1.0f);
        
        addAndMakeVisible(_wet);
        _wet.setRange(0.f, 1.f);
        _wet.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _wet.onValueChange = [this, onChange]{ _state.wetMix = _wet.getValue(); onChange(); };
        _wet.setValue(0.5f);
    }

    void paint (juce::Graphics& g) override
    {
        
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        const auto width = bounds.getWidth() * 0.25;
        _delaySamples.setBounds(bounds.removeFromLeft(width));
        _feedback.setBounds(bounds.removeFromLeft(width));
        _dry.setBounds(bounds.removeFromLeft(width));
        _wet.setBounds(bounds);
    }

private:
    
    juce::Slider _delaySamples, _feedback, _dry, _wet;
    juce::Label _delaySamplesLabel, _feebackLabel, _dryLabel, _wetLabel;
    Delay::State& _state;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayGUI)
};
