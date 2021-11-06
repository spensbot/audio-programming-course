/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , _visualizer(p._generator_t, p._generatorState, p._chainState)
    , _levelGUI("Level", std::make_unique<LevelGUI>(p._chainState.levelState, [this]{ _visualizer.update(); }))
    , _saturatorGUI("Saturation", std::make_unique<SaturatorGUI>(p._chainState.saturatorState, [this]{ _visualizer.update(); }))
    , _delayGUI("Delay", std::make_unique<DelayGUI>(p._chainState.delayState, [this]{ _visualizer.update(); }))
    , _lowPassGUI("Low Pass Filter", std::make_unique<LowPassGUI>(p._chainState.lowPassState, [this]{ _visualizer.update(); }))
    , _compressorGUI("Compressor", std::make_unique<CompressorGUI>(p._chainState.compressorState, [this]{ _visualizer.update(); }))
    , _generatorGUI(p._generatorState, p._generator_t, [this]{ _visualizer.update(); })
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1500, 1000);
    addAndMakeVisible(_levelGUI);
    addAndMakeVisible(_saturatorGUI);
    addAndMakeVisible(_delayGUI);
    addAndMakeVisible(_lowPassGUI);
    addAndMakeVisible(_compressorGUI);
    addAndMakeVisible(_visualizer);
    addAndMakeVisible(_generatorGUI);
    addAndMakeVisible(_windowSeconds);
    
    _windowSeconds.setRange(0.05, 2.0);
    _windowSeconds.setTextValueSuffix("s");
    _windowSeconds.setValue(0.05);
    _windowSeconds.onValueChange = [this]{ _visualizer.updateWindow(_windowSeconds.getValue()); };
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    
}

void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void NewProjectAudioProcessorEditor::resized()
{
    const auto padding = 10;
    
    auto bounds = getLocalBounds();
    bounds.reduce(padding, padding);
    
    auto width = bounds.getWidth() - padding * 4;
    auto topBounds = bounds.removeFromTop(bounds.getHeight() * 0.4);
    _levelGUI.setBounds(topBounds.removeFromLeft(width * 0.15));
    topBounds.removeFromLeft(padding);
    _saturatorGUI.setBounds(topBounds.removeFromLeft(width * 0.15));
    topBounds.removeFromLeft(padding);
    _delayGUI.setBounds(topBounds.removeFromLeft(width * 0.275));
    topBounds.removeFromLeft(padding);
    _lowPassGUI.setBounds(topBounds.removeFromLeft(width * 0.15));
    topBounds.removeFromLeft(padding);
    _compressorGUI.setBounds(topBounds);
    
    bounds.removeFromTop(padding);
    
    _visualizer.setBounds(bounds);
    _windowSeconds.setBounds(bounds.removeFromBottom(30));
    _generatorGUI.setBounds(bounds.removeFromRight(width * 0.2));
}
