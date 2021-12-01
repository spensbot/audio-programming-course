/*
  ==============================================================================

    Generator.h
    Created: 5 Nov 2021 10:01:37pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <cmath>

class Generator {
public:
    struct State {
        float duration = 0.25;
        float hz = 300.0;
        float harmonic = 0.0;
        bool isGenerated = true;
    };
    
    Generator(State& state, float& t): _state(state), _t(t) {}
    
    void prepare(double sampleRate) {
        _t = 0.f;
        _sampleRate = sampleRate;
    }
    
    float getNextSample() {
        if (_t < _state.duration) {
            auto twoPi = juce::MathConstants<double>::twoPi; // radians / oscillation
            auto radsPerSecond = twoPi * _state.hz;
            auto rads = radsPerSecond * _t;
            
            auto hRadsPerSecond = twoPi * _state.hz * 16.f;
            auto hRads = hRadsPerSecond * _t;
            
            _t += 1.f / _sampleRate;
            
            return std::sin(rads) + std::sin(hRads) * _state.harmonic;
        } else {
            _t += 1.f / _sampleRate;
            return 0.f;
        }
    }
    
private:
    double _sampleRate;
    
    State& _state;
    float& _t;
};
