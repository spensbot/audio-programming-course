/*
  ==============================================================================

    Saturator.h
    Created: 31 Oct 2021 10:52:12am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Processor.h"

class Saturator : public Processor {
public:
    struct State {
        float saturation = 1.f; // 1 to 100
    };
    
    Saturator(State& state): _state(state) {}
    
    float processSample(float sample) override {
        if (sample > 0.f) {
            return 1.0f - powf(1.0f-sample, _state.saturation);
        } else {
            return -(1.0f - powf(1.0f+sample, _state.saturation));
        }
    }
    
private:
    State& _state;
};
