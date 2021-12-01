/*
  ==============================================================================

    RecircBuffer.h
    Created: 2 Nov 2021 10:59:11pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <vector>

class RecircBuffer {
public:
    void reset() {
        index = 0;
        std::fill(_buffer.begin(), _buffer.end(), 0.f);
    }
    
    void prepare(double sampleRate, float seconds) {
        
    }
    
    void setSize(int size) {
        _buffer.resize(size);
    }
    
    float getNext(float sampleIn, int delaySamples, float feedbackLevel){
        const auto sampleOut = getSample(delaySamples);
        push(sampleIn + sampleOut * feedbackLevel);
        increment();
        return sampleOut;
    }
    
    float getSampleBySeconds(float delaySeconds) {
        
    }
    
    float getAvgAbs(int delaySamplesStart, int numSamples) {
        auto sum = 0.f;
        for (auto i=0 ; i<numSamples ; i++) {
            sum += std::abs(getSample(delaySamplesStart + i));
        }
        return sum / numSamples;
    }
    
    void push(float sample){
        _buffer[index] = sample;
    }
    
private:
    void increment(){
        index += 1;
        index %= _buffer.size();
    }
    
    float getSample(int delaySamples){
        int delayIndex = index - delaySamples;
        if (delayIndex < 0){
            delayIndex = int(_buffer.size()) + delayIndex;
        }
        return _buffer[delayIndex];
    }
    
    std::vector<float> _buffer;
    int index = 0;
};
