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
    , _levelGUI("Level", std::make_unique<LevelGUI>(p._chainState.levelState, [this]{ _visualizer.update(); }))
    , _saturatorGUI("Saturation", std::make_unique<SaturatorGUI>(p._chainState.saturatorState, [this]{ _visualizer.update(); }))
    , _delayGUI("Delay", std::make_unique<DelayGUI>(p._chainState.delayState, [this]{ _visualizer.update(); }))
    , _lowPassGUI("Low Pass Filter", std::make_unique<LowPassGUI>(p._chainState.lowPassState, [this]{ _visualizer.update(); }))
    , _compressorGUI("Compressor", std::make_unique<CompressorGUI>(p._chainState.compressorState, [this]{ _visualizer.update(); }))
    , _visualizer(p._generator_t, p._generatorState, p._chainState)
    , _visualizerLive(p._generatorState, p._inBuffer, p._outBuffer)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
//    setSize (1500, 1000);
    setSize (1300, 750);
    setResizable(true, true);
    setResizeLimits(500, 300, 1920, 1080);
    addAndMakeVisible(_levelGUI);
    addAndMakeVisible(_saturatorGUI);
    addAndMakeVisible(_delayGUI);
    addAndMakeVisible(_lowPassGUI);
    addAndMakeVisible(_compressorGUI);
    addAndMakeVisible(_visualizerLive);
    addAndMakeVisible(_visualizer);
    addAndMakeVisible(_isGenerated);
    _isGenerated.setButtonText("Generate Audio");
    _isGenerated.onClick = [&p, this]{
        p._generatorState.isGenerated = _isGenerated.getToggleState();
    };
    _isGenerated.setToggleState(true, juce::NotificationType::sendNotification);
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
    auto topLeftBounds = topBounds.removeFromLeft(width * 0.15);
    _isGenerated.setBounds(topLeftBounds.removeFromTop(40));
    _levelGUI.setBounds(topLeftBounds);
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
}
