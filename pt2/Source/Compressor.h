/*
  ==============================================================================

    CompressorGUI.h
    Created: 31 Oct 2021 10:41:42am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "Processor.h"

class Compressor : public Processor {
public:
    struct State {
        float threshold;
        float ratio;
        float attack;
        float release;
    };
    
    Compressor(State& state): _state(state) {}
    
    float processSample(float sample) override {
        return sample;
    }
    
private:
    State& _state;
};
