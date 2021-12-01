/*
  ==============================================================================

    DelayGui.h
    Created: 31 Oct 2021 10:46:08am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "RecircBuffer.h"
#include "Processor.h"

class Delay : public Processor {
public:
    struct State {
        float delaySeconds = 0.0; // 0 to 1
        float feedback = 0.0; // 0 to 1
        float dryMix = 1.0; // 0 to 1
        float wetMix = 0.0; // 0 to 1
    };
    
    Delay(State& state): _state(state) {}
    
    virtual void prepare(double sampleRate) override {
        _sampleRate = sampleRate;
        _buffer.setSize(100000);
        _buffer.reset();
    }
    
    float processSample(float sample) override {
        const auto delaySamples = static_cast<int>(_sampleRate * _state.delaySeconds);
        auto wetSample = _buffer.getNext(sample, delaySamples, _state.feedback);
        return sample * _state.dryMix + wetSample * _state.wetMix;
    }
    
private:
    State& _state;
    RecircBuffer _buffer;
    double _sampleRate = 44000.0;
};

