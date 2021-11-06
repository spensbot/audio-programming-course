/*
  ==============================================================================

    ProcessorBase.h
    Created: 31 Oct 2021 11:01:15am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Processor {
public:
    // Called by GUI thread before processing begins. Allocate any necessary heap memory.
    virtual void prepare(double sampleRate) {};
    
    // Called by Audio thread. Do not lock!!!
    virtual float processSample(float sample) = 0;
    
    virtual ~Processor() {};
    
    //    virtual void process(float* monoChannelData, size_t numSamples) = 0;
};
