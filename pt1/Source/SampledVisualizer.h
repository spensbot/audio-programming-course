#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SampledVisualizer : public juce::Component
{
public:
    SampledVisualizer() {}

    ~SampledVisualizer() {}
    
    void reset (double level, double hz, std::optional<double> displaySampleRate)
    {
        m_level = level;
        m_hz = hz;
        m_displaySampleRate = displaySampleRate;
        update();
    }

    void paint (juce::Graphics& g) override
    {
        int height = getHeight();
        auto x = 0.0;
        const auto y_ = double (height / 2);
        const auto amplitude = double (height / 2);
        
        g.setColour (juce::Colour::fromHSV(0.0f,0.0f,1.0f,1.0f));
        
        g.drawLine(x, y_, getWidth(), y_, LINE_THICKNESS);
        
        for (int i=0 ; i<m_samples.size()-1 ; ++i) {
            auto x0 = x;
            auto x1 = x0 + STEP_SIZE;
            auto y0 = y_ - m_samples[i] * amplitude;
            auto y1 = y_ - m_samples[i+1] * amplitude;
            g.drawLine(x0, y0, x1, y1, LINE_THICKNESS);
            
            x = x1;
        }
        
        if (m_displaySampleRate) {
            x = 0.0;
            auto pixelsPerSecond = getWidth() / LENGTH;
            auto pixelsPerSample = pixelsPerSecond / *m_displaySampleRate;
            
            while (x < getWidth()) {
                int xInt = x;
                auto y = y_ - m_samples[xInt] * amplitude;
                g.drawEllipse(x - 5, y - 5, 10, 10, LINE_THICKNESS);
                
                x += pixelsPerSample;
            }
        }
    }

    void resized() override
    {
        update();
    }
    
    void update() {
        const auto numSteps = getWidth() / STEP_SIZE;
        const auto numSamples = numSteps + 1;
        m_samples.resize(numSamples);
        
        auto twoPi = juce::MathConstants<double>::twoPi; // radians / oscillation
        auto radiansPerSecond = twoPi * m_hz;
        auto secondsPerSample = LENGTH / m_samples.size();
        auto radiansPerSample = radiansPerSecond * secondsPerSample;
        
        auto rads = 0.0;
        for (auto& sample : m_samples) {
            sample = std::sin(rads) * m_level;
            rads += radiansPerSample;
        }
        
        repaint();
    }

private:
    const int STEP_SIZE = 1; // pixels
    const double LENGTH = 0.05; // seconds (1/20)
    const double LINE_THICKNESS = 2.0; // pixels
    
    double m_level;
    double m_hz;
    std::optional<double> m_displaySampleRate;
    std::vector<double> m_samples;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampledVisualizer)
};
