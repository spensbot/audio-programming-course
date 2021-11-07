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
        
        addAndMakeVisible(_delaySeconds);
        LabelledSlider::Options o{};
        o.onChange = [this, onChange] (float val) { _state.delaySeconds = val; onChange(); };
        o.init = 0.5f;
        o.label = "Delay";
        o.suffix = "s";
        _delaySeconds.setup(o);
        
        addAndMakeVisible(_feedback);
        o = {};
        o.onChange = [this, onChange] (float val) { _state.feedback = val; onChange(); };
        o.init = 0.0f;
        o.label = "Feedback";
        _feedback.setup(o);
        
        addAndMakeVisible(_dry);
        o = {};
        o.onChange = [this, onChange] (float val) { _state.dryMix = val; onChange(); };
        o.init = 1.f;
        o.label = "Dry Mix";
        _dry.setup(o);
        
        addAndMakeVisible(_wet);
        o = {};
        o.onChange = [this, onChange] (float val) { _state.wetMix = val; onChange(); };
        o.init = 0.f;
        o.label = "Wet Mix";
        _wet.setup(o);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        const auto width = bounds.getWidth() * 0.25;
        _delaySeconds.setBounds(bounds.removeFromLeft(width));
        _feedback.setBounds(bounds.removeFromLeft(width));
        _dry.setBounds(bounds.removeFromLeft(width));
        _wet.setBounds(bounds);
    }

private:
    
    LabelledSlider _delaySeconds, _feedback, _dry, _wet;
    Delay::State& _state;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayGUI)
};
