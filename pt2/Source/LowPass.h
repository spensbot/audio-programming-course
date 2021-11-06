/*
  ==============================================================================

    LowPassGui.h
    Created: 31 Oct 2021 10:45:09am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "RollingAverage.h"
#include "Processor.h"

class LowPass : public Processor {
public:
    struct State {
        float frequency = 20000.f; // 20 - 20000
    };
    
    LowPass(State& state): _state(state) {}
    
    void prepare(double sampleRate) override {
        _sampleRate = sampleRate;
        _rollingAverage.reset();
    }
    
    float processSample(float sample) override {
        if (_state.frequency != _lastFrequency) {
            _rollingAverage.setSustainSeconds(_sampleRate, 1.f/_state.frequency);
            _lastFrequency = _state.frequency;
        }
        _rollingAverage.push(sample);
        return _rollingAverage.get();
    }
    
private:
    State& _state;
    float _lastFrequency = 20000.f;
    double _sampleRate;
    RollingAverage _rollingAverage;
};
