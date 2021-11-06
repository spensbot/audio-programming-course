/*
  ==============================================================================

    Level.h
    Created: 31 Oct 2021 10:50:11am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Processor.h"

class Level : public Processor {
public:
    struct State {
        float level; // 0 to 1
    };
    
    Level(State& state): _state(state) {}
    
    float processSample(float sample) override {
        return sample * _state.level;
    }
    
private:
    State& _state;
};
