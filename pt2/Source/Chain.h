#pragma once

#include "Processor.h"
#include "Level.h"
#include "Saturator.h"
#include "Delay.h"
#include "LowPass.h"
#include "Compressor.h"
#include "Generator.h"

class Chain : public Processor {
public:
    struct State {
        Level::State levelState;
        Saturator::State saturatorState;
        Delay::State delayState;
        LowPass::State lowPassState;
        Compressor::State compressorState;
    };
    
    Chain(State& state): _state(state)
    {
        _processors.push_back(std::make_unique<Level>(_state.levelState));
        _processors.push_back(std::make_unique<Saturator>(_state.saturatorState));
        _processors.push_back(std::make_unique<Delay>(_state.delayState));
        _processors.push_back(std::make_unique<LowPass>(_state.lowPassState));
        _processors.push_back(std::make_unique<Compressor>(_state.compressorState));
    }
    
    // Called by GUI thread before processing begins. Allocate any necessary heap memory.
    void prepare(double sampleRate) override {
        for (const auto& processor : _processors) {
            processor->prepare(sampleRate);
        }
    };
    
    // Called by Audio thread. Do not lock!!!
    float processSample(float sample) override {
        for (const auto& processor : _processors) {
            sample = processor->processSample(sample);
        }
        return sample;
    };
    
private:
    std::vector<std::unique_ptr<Processor>> _processors;
    
    State& _state;
};
