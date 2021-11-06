/*
  ==============================================================================

    GeneratorGUI.h
    Created: 5 Nov 2021 10:31:21pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Generator.h"

//==============================================================================
/*
*/
class GeneratorGUI  : public juce::Component
{
public:
    GeneratorGUI(Generator::State& state, float& t, std::function<void()> onChange): _state(state), _t(t)
    {
        addAndMakeVisible(_duration);
        _duration.setRange(0.05, 1.0);
        _duration.setTextValueSuffix("s");
        _duration.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _duration.onValueChange = [this, onChange]{ _state.duration = _duration.getValue(); onChange(); };
        _duration.setValue(0.05);
        
        addAndMakeVisible(_hz);
        _hz.setRange(20, 20000);
        _hz.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        _hz.setSkewFactorFromMidPoint(500.0);
        _hz.setTextValueSuffix("Hz");
        _hz.onValueChange = [this, onChange]{ _state.hz = _hz.getValue(); onChange(); };
        _hz.setValue(20);
        
        addAndMakeVisible(_replay);
        _replay.setButtonText("Replay");
        _replay.onClick = [this]{ _t = 0.f; };
    }

    ~GeneratorGUI() override
    {
    }

    void paint (juce::Graphics& g) override
    {
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _replay.setBounds(bounds.removeFromBottom(30));
        bounds.removeFromBottom(10);
        
        auto width = (bounds.getWidth() - 10) / 2;
        
        _hz.setBounds(bounds.removeFromLeft(width));
        bounds.removeFromLeft(10);
        _duration.setBounds(bounds);
    }

private:
    Generator::State& _state;
    float& _t;
    juce::Slider _hz, _duration;
    juce::TextButton _replay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GeneratorGUI)
};
