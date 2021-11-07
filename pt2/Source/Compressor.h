/*
  ==============================================================================

    CompressorGUI.h
    Created: 31 Oct 2021 10:41:42am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Processor.h"

#include "RollingAverage.h"

class Compressor : public Processor {
public:
    struct State {
        float threshold = 1.f;
        float ratio = 1.f;
        float attack = 1.f;
        float release = 1.f;
    };
    
    Compressor(State& state): _state(state) {}
    
    void prepare(double sampleRate) override {
        _averageAbs.reset();
        _sampleRate = sampleRate;
    }
    
    void updateAvg(float sample) {
        if (_state.attack != _lastAttack || _state.release != _lastRelease) {
            _lastAttack = _state.attack;
            _lastRelease = _state.release;
            _averageAbs.setSustainSeconds(_sampleRate, _state.attack / 1000.f, _state.release / 1000.f);
        }
        
        _averageAbs.push(std::fabs(sample));
    }
    
    float getAvg() {
        return _averageAbs.get();
    }
    
    float getCorrection() {
        if (getAvg() > _state.threshold) {
            const auto dif = getAvg() - _state.threshold;
            const auto corrected = _state.threshold + dif / _state.ratio;
            return corrected / getAvg();
        } else {
            return 1.f;
        }
    }
    
    float processSample(float sample) override {
        updateAvg(sample);
        
        return sample * getCorrection();
        
//        if (sample > 0.f) {
//            if (sample > _state.threshold) {
//                const auto dif = sample - _state.threshold;
//                return _state.threshold + dif / _state.ratio;
//            }
//        } else {
//            if (sample < -_state.threshold) {
//                const auto dif = sample + _state.threshold;
//                return -_state.threshold + dif / _state.ratio;
//            }
//        }
    }
    
private:
    State& _state;
    double _sampleRate;
    float _lastAttack, _lastRelease;
    RollingAverageBiased _averageAbs;
};
