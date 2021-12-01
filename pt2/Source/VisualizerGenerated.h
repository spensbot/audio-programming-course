/*
  ==============================================================================

    VisualizerGenerated.h
    Created: 31 Oct 2021 10:49:48am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Chain.h"
#include "Generator.h"
#include "VisualizerTiming.h"
#include "VisualizerState.h"

class VisualizerGenerated : public juce::Component
{
public:    
    VisualizerGenerated(VisualizerState& state, Generator::State& generatorState, Chain::State& chainState)
        : _state(state)
        , _generator(generatorState, _localGenerator_t)
        , _generatorState(generatorState)
        , _compressor(chainState.compressorState)
    {
        _processors.push_back(std::make_unique<Level>(chainState.levelState));
        _processors.push_back(std::make_unique<Saturator>(chainState.saturatorState));
        _processors.push_back(std::make_unique<Delay>(chainState.delayState));
        _processors.push_back(std::make_unique<LowPass>(chainState.lowPassState));
//        _processors.push_back(std::make_unique<Compressor>(chainState.compressorState));
    }

    void paint (juce::Graphics& g) override
    {
        if (_generatorState.isGenerated) {
            int height = getHeight();
            auto x = 0.0;
            const auto y_ = double (height / 2);
            const auto amplitude = double (height / 2);

            g.setColour (juce::Colour::fromHSV(0.0f,0.0f,1.0f,1.0f));
            g.drawLine(x, y_, getWidth(), y_, LINE_THICKNESS);

            for (int i=0 ; i<_samples.size()-1 ; ++i) {
                const auto [generatedSample0, processedSample0, compAvg0, compCorrection0] = _samples[i];
                const auto [generatedSample1, processedSample1, compAvg1, compCorrection1] = _samples[i+1];
                
                auto x0 = x;
                auto x1 = x0 + STEP_SIZE;
                auto y0 = y_ - generatedSample0 * amplitude;
                auto y1 = y_ - generatedSample1 * amplitude;
                if (_state.inSignal) {
                    g.setColour (juce::Colour::fromHSV(0.0f,1.0f,1.0f,1.0f));
                    g.drawLine(x0, y0, x1, y1, LINE_THICKNESS);
                }

                if (_state.outSignal) {
                    g.setColour (juce::Colour::fromHSV(0.5f,1.0f,1.0f,1.0f));
                    y0 = y_ - processedSample0 * amplitude;
                    y1 = y_ - processedSample1 * amplitude;
                    g.drawLine(x0, y0, x1, y1, LINE_THICKNESS);
                }
                
                if (_state.threshold) {
                    g.setColour (juce::Colour::fromHSV(0.0f,0.0f, 0.5f, 1.0f));
                    y0 = y_ - _compressor.getThreshold() * amplitude;
                    g.drawLine(0.0, y0, getWidth(), y0, LINE_THICKNESS);
                }

                if (_state.avgLevel) {
                    g.setColour (juce::Colour::fromHSV(0.75f,1.0f,1.0f,1.0f));
                    y0 = y_ - compAvg0 * amplitude;
                    y1 = y_ - compAvg1 * amplitude;
                    g.drawLine(x0, y0, x1, y1, LINE_THICKNESS);
                }

                if (_state.compression) {
                    g.setColour (juce::Colour::fromHSV(0.25f,1.0f,1.0f,1.0f));
                    y0 = y_ - compCorrection0 * amplitude;
                    y1 = y_ - compCorrection1 * amplitude;
                    g.drawLine(x0, y0, x1, y1, LINE_THICKNESS);
                }
                
                x = x1;
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
        _samples.resize(numSamples);

        const auto sampleRate = numSamples / _state.windowSeconds;
        _generator.prepare(sampleRate);
        for (auto& processor : _processors) {
            processor->prepare(sampleRate);
        }
        _compressor.prepare(sampleRate);

        for (auto& [generatedSample, processedSample, compAvg, compCorrection] : _samples) {
            generatedSample = _generator.getNextSample();
            processedSample = generatedSample;
            for (auto& processor : _processors) {
                processedSample = processor->processSample(processedSample);
            }
            processedSample = _compressor.processSample(processedSample);
            compAvg = _compressor.getAvg();
            compCorrection = _compressor.getCorrection();
        }

        repaint();
    }

private:
    const int STEP_SIZE = 1; // pixels
    const double LINE_THICKNESS = 2.0; // pixels
    
    VisualizerState& _state;

    float _localGenerator_t;
    Generator _generator;
    Generator::State& _generatorState;
    std::vector<std::unique_ptr<Processor>> _processors;
    Compressor _compressor;
            
    std::vector<std::tuple<float, float, float, float>> _samples;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualizerGenerated)
};
