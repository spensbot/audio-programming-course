/*
  ==============================================================================

    Visualizer.h
    Created: 31 Oct 2021 10:49:48am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Chain.h"
#include "Generator.h"

class Visualizer : public juce::Component
{
public:
    Visualizer(float& generator_t, Generator::State& generatorState, Chain::State& chainState)
        : _generator_t(generator_t)
        , _generator(generatorState, _localGenerator_t) {
        _processors.push_back(std::make_unique<Level>(chainState.levelState));
        _processors.push_back(std::make_unique<Saturator>(chainState.saturatorState));
        _processors.push_back(std::make_unique<Delay>(chainState.delayState));
        _processors.push_back(std::make_unique<LowPass>(chainState.lowPassState));
        _processors.push_back(std::make_unique<Compressor>(chainState.compressorState));
    }
    
    void updateWindow(float windowSeconds) { _windowSeconds = windowSeconds; update(); }

    void paint (juce::Graphics& g) override
    {
        int height = getHeight();
        auto x = 0.0;
        const auto y_ = double (height / 2);
        const auto amplitude = double (height / 2);

        g.setColour (juce::Colour::fromHSV(0.0f,0.0f,1.0f,1.0f));
        g.drawLine(x, y_, getWidth(), y_, LINE_THICKNESS);

        for (int i=0 ; i<_samples.size()-1 ; ++i) {
            const auto [generatedSample0, processedSample0] = _samples[i];
            const auto [generatedSample1, processedSample1] = _samples[i+1];
            
            g.setColour (juce::Colour::fromHSV(0.0f,1.0f,1.0f,1.0f));
            auto x0 = x;
            auto x1 = x0 + STEP_SIZE;
            auto y0 = y_ - generatedSample0 * amplitude;
            auto y1 = y_ - generatedSample1 * amplitude;
            g.drawLine(x0, y0, x1, y1, LINE_THICKNESS);
            
            g.setColour (juce::Colour::fromHSV(0.5f,1.0f,1.0f,1.0f));
            y0 = y_ - processedSample0 * amplitude;
            y1 = y_ - processedSample1 * amplitude;
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

        const auto sampleRate = numSamples / _windowSeconds;
        _generator.prepare(sampleRate);
        for (auto& processor : _processors) {
            processor->prepare(sampleRate);
        }

        for (auto& [generatedSample, processedSample] : _samples) {
            generatedSample = _generator.getNextSample();
            processedSample = generatedSample;
            for (auto& processor : _processors) {
                processedSample = processor->processSample(processedSample);
            }
            std::cout << processedSample << std::endl;
        }

        repaint();
    }

private:
    const int STEP_SIZE = 1; // pixels
    const double LINE_THICKNESS = 2.0; // pixels
    
    float& _generator_t;
    float _localGenerator_t;
    Generator _generator;
    std::vector<std::unique_ptr<Processor>> _processors;
            
    std::vector<std::tuple<float, float>> _samples;
                                                     
    float _windowSeconds = 1.f;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
};
