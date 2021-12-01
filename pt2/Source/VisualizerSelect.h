/*
  ==============================================================================

    VisualizerSelect.h
    Created: 9 Nov 2021 11:56:41pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "VisualizerState.h"

//==============================================================================
/*
*/
class VisualizerSelect  : public juce::Component
{
public:
    
    VisualizerSelect(VisualizerState& state, std::function<void()> onChange)
    : _inSignal("In")
    , _outSignal("Out")
    , _threshold("Threshold")
    , _avgLevel("Avg. Level")
    , _compression("Compression")
    , _state(state)
    , _onChange(onChange)
    {
        for (auto* button : _buttons) {
            addAndMakeVisible(button);
        }
        _inSignal.onClick = [this]{ _state.inSignal = _inSignal.getToggleState();  _onChange(); };
        _inSignal.setToggleState(true, juce::NotificationType::sendNotification);
        _outSignal.onClick = [this]{ _state.outSignal = _outSignal.getToggleState(); _onChange(); };
        _outSignal.setToggleState(true, juce::NotificationType::sendNotification);
        _threshold.onClick = [this]{ _state.threshold = _threshold.getToggleState(); _onChange(); };
        _avgLevel.onClick = [this]{ _state.avgLevel = _avgLevel.getToggleState(); _onChange(); };
        _compression.onClick = [this]{ _state.compression = _compression.getToggleState(); _onChange(); };
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colour::fromHSV(0.0, 0.0, 0.0, 0.3));
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        auto bounds = getLocalBounds();
        const auto padding = 3.0;
        const auto height = (bounds.getHeight() - 3.0*padding) / 4.0;
        
        auto topBounds = bounds.removeFromTop(height);
        _inSignal.setBounds(topBounds.removeFromLeft(topBounds.getWidth()/2.0));
        _outSignal.setBounds(topBounds);
        bounds.removeFromTop(padding);
        _threshold.setBounds(bounds.removeFromTop(height));
        bounds.removeFromTop(padding);
        _avgLevel.setBounds(bounds.removeFromTop(height));
        bounds.removeFromTop(padding);
        _compression.setBounds(bounds.removeFromTop(height));
    }
    
    juce::ToggleButton _inSignal, _outSignal, _threshold, _avgLevel, _compression;

private:
    VisualizerState& _state;
    std::function<void()> _onChange;
    std::vector<juce::ToggleButton*> _buttons = {&_inSignal, &_outSignal, &_threshold, &_avgLevel, &_compression};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualizerSelect)
};
