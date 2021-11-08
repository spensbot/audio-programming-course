/*
  ==============================================================================

    TransferFunctionVisualizer.h
    Created: 6 Nov 2021 7:52:19pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Saturator.h"

//==============================================================================
/*
*/
class TransferFunctionVisualizer  : public juce::Component
{
public:
    TransferFunctionVisualizer(Saturator::State& saturatorState): _saturator(saturatorState)  {
        update();
    }

    void paint (juce::Graphics& g) override
    {
        int height = getHeight();
        auto x = 0.0;
        const auto y_ = double (height / 2);
        const auto x_ = double (getWidth() / 2);
        const auto amplitude = double (height / 2);
        
        g.fillAll(juce::Colour::fromHSV(0.0f,0.0f,0.0f,1.0f));

        g.setColour (juce::Colour::fromHSV(0.0f,0.0f,0.5f,1.0f));
        g.drawLine(x, y_, getWidth(), y_, LINE_THICKNESS);
        g.drawLine(x_, 0.0, x_, height, LINE_THICKNESS);

        for (int i=0 ; i<_samples.size()-1 ; ++i) {
            const auto sample0 = _samples[i];
            const auto sample1 = _samples[i+1];
            
            auto x0 = x;
            auto x1 = x0 + STEP_SIZE;
            
            g.setColour (juce::Colour::fromHSV(0.0f,0.0f,1.0f,1.0f));
            auto y0 = y_ - sample0 * amplitude;
            auto y1 = y_ - sample1 * amplitude;
            g.drawLine(x0, y0, x1, y1, LINE_THICKNESS);
            
            x = x1;
        }
    }

    void resized() override
    {
        update();
    }
    
    void update() {
        const auto numSteps = getWidth() / STEP_SIZE;
        const auto numSamples = numSteps + 1;
        _samples.resize(numSamples);
        
        auto x = -1.f;
        const auto delta = 2.f / numSteps;

        for (auto& sample : _samples) {
            sample = _saturator.processSample(x);
            x += delta;
        }

        repaint();
    }

private:
    const int STEP_SIZE = 1; // pixels
    const double LINE_THICKNESS = 2.0; // pixels
            
    std::vector<float> _samples;
    Saturator _saturator;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransferFunctionVisualizer)
};
