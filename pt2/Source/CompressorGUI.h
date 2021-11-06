/*
  ==============================================================================

    CompressorGUI.h
    Created: 31 Oct 2021 10:57:05am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Compressor.h"

class CompressorGUI : public juce::Component
{
public:
    CompressorGUI(Compressor::State& state, std::function<void()> onChange): _state(state) {
        
    }

    void paint (juce::Graphics& g) override
    {
        
    }

    void resized() override
    {
        
    }

private:
    Compressor::State& _state;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorGUI)
};
