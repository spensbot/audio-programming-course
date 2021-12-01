/*
  ==============================================================================

    CompressorGUI.h
    Created: 31 Oct 2021 10:57:05am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Compressor.h"
#include "LabelledSlider.h"

class CompressorGUI : public juce::Component
{
public:
    CompressorGUI(Compressor::State& state, std::function<void()> onChange): _state(state) {
        addAndMakeVisible(_threshold);
        LabelledSlider::Options o{};
        o.onChange = [this, onChange] (float val) { _state.threshold = val; onChange(); };
        o.init = 1.f;
        o.label = "Threshold";
        _threshold.setup(o);
        
        addAndMakeVisible(_ratio);
        o = {};
        o.onChange = [this, onChange] (float val) { _state.ratio = val; onChange(); };
        o.min = 1.f;
        o.max = 10.f;
        o.init = 1.f;
        o.label = "Ratio";
        _ratio.setup(o);
        
        addAndMakeVisible(_attack);
        o = {};
        o.onChange = [this, onChange] (float val) { _state.attack = val; onChange(); };
        o.min = 0.f;
        o.max = 100.f;
        o.init = 0.f;
        o.label = "Attack";
        o.suffix = "ms";
        _attack.setup(o);
        
        addAndMakeVisible(_release);
        o = {};
        o.onChange = [this, onChange] (float val) { _state.release = val; onChange(); };
        o.min = 0.f;
        o.max = 500.f;
        o.init = 0.f;
        o.label = "Release";
        o.suffix = "ms";
        _release.setup(o);
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        const auto width = bounds.getWidth() * 0.25;
        _threshold.setBounds(bounds.removeFromLeft(width));
        _ratio.setBounds(bounds.removeFromLeft(width));
        _attack.setBounds(bounds.removeFromLeft(width));
        _release.setBounds(bounds);
    }

private:
    LabelledSlider _threshold, _ratio, _attack, _release;
    Compressor::State& _state;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorGUI)
};
