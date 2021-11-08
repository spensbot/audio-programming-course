/*
  ==============================================================================

    VisualizerTiming.h
    Created: 6 Nov 2021 7:52:53pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VisualizerTiming  : public juce::Component
{
public:
    VisualizerTiming() {}
    
    void reset(float windowSeconds) {
        _windowSeconds = windowSeconds;
        repaint();
    }

    void paint (juce::Graphics& g) override
    {
        auto delta = 1.f;
        
        while (_windowSeconds / delta < 1.5f) {
            delta = delta / 5.f;
        }
        
        std::vector<float> lines;
        
        auto t = delta;
        while (t < _windowSeconds) {
            lines.push_back(t);
            t += delta;
        }
        
        auto xMin = 0.0;
        const auto xMax = getWidth();
        const auto yMin = 0.0;
        const auto y_ = double (getHeight() / 2);
        const auto yMax = getHeight();

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        
        for (const auto line : lines) {
            const auto x = line / _windowSeconds * xMax;
            g.drawLine (x, yMin, x, yMax, LINE_THICKNESS);
            const auto string = juce::String::toDecimalStringWithSignificantFigures(line, 1) + "s";
            g.drawText (string, juce::Rectangle<float>(x, y_, 60, 30), juce::Justification::left, true);
        }
    }

private:
    float _windowSeconds;
    
    const double LINE_THICKNESS = 1.0; // pixels
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualizerTiming)
};
