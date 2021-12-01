/*
  ==============================================================================

    VisualizerLive.h
    Created: 10 Nov 2021 11:11:02pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RecircBuffer.h"
#include "VisualizerState.h"
#include "Generator.h"

//==============================================================================
/*
*/
class VisualizerLive  : public juce::Component
{
public:
    VisualizerLive(VisualizerState& visualizerState, Generator::State& generatorState, RecircBuffer& inBuffer, RecircBuffer& outBuffer)
    : _inBuffer(inBuffer)
    , _outBuffer(outBuffer)
    , _visualizerState(visualizerState)
    , _generatorState(generatorState)
    {
        
    }

    ~VisualizerLive() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        if (!_generatorState.isGenerated) {
            int height = getHeight();
            const auto y_ = double (height / 2);
            const auto amplitude = double (height / 2);

            g.setColour (juce::Colour::fromHSV(0.0f,0.0f,1.0f,1.0f));
            g.drawLine(0.0, y_, getWidth(), y_, LINE_THICKNESS);
            
            auto x = 0.0;
            g.setColour (juce::Colour::fromHSV(0.0f,1.0f,1.0f,1.0f));
            if (_visualizerState.inSignal) {
                for (int i=0 ; i<_inAvg.size() ; ++i) {
                    const auto avg = _inAvg[i];
                    g.drawLine(x, avg * amplitude, x, -avg * amplitude, STEP_SIZE);
                    
                    x += STEP_SIZE;
                }
            }
            
            x = 0.0;
            g.setColour (juce::Colour::fromHSV(0.5f,1.0f,1.0f,1.0f));
            if (_visualizerState.outSignal) {
                for (int i=0 ; i<_outAvg.size() ; ++i) {
                    const auto avg = _outAvg[i];

                    g.drawLine(x, avg * amplitude, x, -avg * amplitude, STEP_SIZE);
                    
                    x += STEP_SIZE;
                }
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
        const auto secondsPerStep = WINDOW / numSteps;
        _inAvg.resize(numSamples);
        _outAvg.resize(numSamples);
        
        auto seconds = 0.0;
        
        for (auto i=0 ; i<numSamples ; i++) {
            _inAvg.data()
            
            seconds += secondsPerStep;
        }
        
        for (auto& avg : _outAvg) {
            avg = 0.f;
        }
        
        repaint();
    }

private:
    const int STEP_SIZE = 1; // pixels
    const double LINE_THICKNESS = 2.0; // pixels
    const double WINDOW = 2.0; // seconds
    
    RecircBuffer& _inBuffer, _outBuffer;
    VisualizerState& _visualizerState;
    Generator::State& _generatorState;
    std::vector<float> _inAvg, _outAvg;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualizerLive)
};
