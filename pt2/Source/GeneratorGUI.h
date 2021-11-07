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
#include "LabelledSlider.h"

//==============================================================================
/*
*/
class GeneratorGUI  : public juce::Component
{
public:
    GeneratorGUI(Generator::State& state, float& t, std::function<void()> onChange): _state(state), _t(t)
    {
        addAndMakeVisible(_duration);
        LabelledSlider::Options o{};
        o.min = 0.05f;
        o.max = 1.f;
        o.onChange = [this, onChange] (float val) { _state.duration = val; onChange(); };
        o.init = 0.05f;
        o.label = "Duration";
        o.suffix = "s";
        _duration.setup(o);
        
        addAndMakeVisible(_hz);
        o = {};
        o.min = 20.f;
        o.max = 20000.f;
        o.onChange = [this, onChange] (float val) { _state.hz = val; onChange(); };
        o.init = 20.f;
        o.skewMidpoint = 500.f;
        o.label = "Frequency";
        o.suffix = "Hz";
        _hz.setup(o);
        
        addAndMakeVisible(_replay);
        _replay.setButtonText("Replay");
        _replay.onClick = [this]{ _t = 0.f; };
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
    LabelledSlider _hz, _duration;
    juce::TextButton _replay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GeneratorGUI)
};
