/*
  ==============================================================================

    Visualizer.h
    Created: 31 Oct 2021 10:49:48am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "VisualizerState.h"
#include "VisualizerSelect.h"
#include "VisualizerGenerated.h"
#include "VisualizerLive.h"
#include "VisualizerTiming.h"
#include "LabelledSlider.h"
#include "VisualizerCursor.h"


class Visualizer : public juce::Component
{
public:
    Visualizer(float& generator_t, Generator::State& generatorState, Chain::State& chainState)
    : _generatorGUI(generatorState, generator_t, [this]{ update(); })
    , _visualizerTiming(_state)
    , _visualizerGenerated(_state, generatorState, chainState)
    , _visualizerSelect(_state, [this]{ update(); })
    , _visualizerCursor(generator_t, _state)
    {
        addAndMakeVisible(_visualizerGenerated);
        addAndMakeVisible(_visualizerTiming);
        addAndMakeVisible(_visualizerCursor);
        addAndMakeVisible(_windowSeconds);
        addAndMakeVisible(_visualizerSelect);
        addAndMakeVisible(_generatorGUI);
        
        LabelledSlider::Options o;
        o.onChange = [this](float newVal){
            _state.windowSeconds = newVal;
            update();
        };
        o.textBox = juce::Slider::TextEntryBoxPosition::NoTextBox;
//        o.label =
//        o.suffix =
        o.min = 0.05;
        o.max = 2.0;
        o.init = 0.05;
        o.horizontal = true;
        _windowSeconds.setup(o);
    }
    
    void update() {
        _visualizerGenerated.update();
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        const auto width = bounds.getWidth();
        _visualizerGenerated.setBounds(bounds);
        _visualizerTiming.setBounds(bounds);
        _visualizerCursor.setBounds(bounds);
        _windowSeconds.setBounds(bounds.removeFromBottom(30));
        _generatorGUI.setBounds(bounds.removeFromRight(width * 0.15));
        _visualizerSelect.setBounds(bounds.removeFromRight(150).removeFromTop(100));
    }
    
    void paint(juce::Graphics& g) override {
        static auto count = 0;
        std::cout << "Visualizer::paint() " << count << std::endl;
        count += 1;
    }

private:
    VisualizerState _state;
    
    GeneratorGUI _generatorGUI;
    VisualizerTiming _visualizerTiming;
    VisualizerGenerated _visualizerGenerated;
    VisualizerSelect _visualizerSelect;
    VisualizerCursor _visualizerCursor;
    
    LabelledSlider _windowSeconds;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
};
