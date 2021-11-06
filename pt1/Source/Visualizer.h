#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

namespace settings {
//const double FREQUENCY_MIN = 1.0; // Hz
//const double FREQUENCY_MAX = 100.0; // Hz
//const double SAMPLE_RATE_MIN = 10.0; // samples / second
//const double SAMPLE_RATE_MAX = 1000.0; // samples / second
//const double WINDOW_SECONDS = 1.0;

const double FREQUENCY_MIN = 20.0; // Hz
const double FREQUENCY_MAX = 20000.0; // Hz
const double SAMPLE_RATE_MIN = 200.0; // samples / second
const double SAMPLE_RATE_MAX = 44100.0; // samples / second
const double WINDOW_SECONDS = 1.0 / 20.0;
}

class Visualizer : public juce::Component
{
public:
    Visualizer() {}

    ~Visualizer() {}
    
    void reset (double level, double hz, bool drawWave, std::optional<double> displaySampleRate)
    {
        m_level = level;
        m_hz = hz;
        m_drawWave = drawWave;
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
        
        if (m_drawWave) {
            for (int i=0 ; i<m_samples.size()-1 ; ++i) {
                auto x0 = x;
                auto x1 = x0 + STEP_SIZE;
                auto y0 = y_ - m_samples[i] * amplitude;
                auto y1 = y_ - m_samples[i+1] * amplitude;
                g.drawLine(x0, y0, x1, y1, LINE_THICKNESS);
                
                x = x1;
            }
        }
        
        if (m_displaySampleRate) {
            x = 0.0;
            auto pixelsPerSecond = getWidth() / settings::WINDOW_SECONDS;
            auto pixelsPerSample = pixelsPerSecond / *m_displaySampleRate;
            
            while (x < getWidth()) {
                int xInt = x;
                auto y = y_ - m_samples[xInt] * amplitude;
                g.drawEllipse(x - 5, y - 5, 10, 10, LINE_THICKNESS);
//                g.fillEllipse(x - 5, y - 5, 8, 8);
                
                auto endY = y_;
                if (std::abs(y - y_) > 5) {
                    endY = y < y_ ? y + 5 : y - 5;
                }
                g.drawLine(x, y_, x, endY, LINE_THICKNESS);
                
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
        auto secondsPerSample = settings::WINDOW_SECONDS / m_samples.size();
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
    const double LINE_THICKNESS = 2.0; // pixels
    
    double m_level;
    double m_hz;
    double m_drawWave;
    std::optional<double> m_displaySampleRate;
    std::vector<double> m_samples;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
};
