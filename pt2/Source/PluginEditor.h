/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GuiSection.h"
#include "LevelGUI.h"
#include "SaturatorGUI.h"
#include "DelayGUI.h"
#include "LowPassGUI.h"
#include "CompressorGUI.h"
#include "GeneratorGUI.h"
#include "Visualizer.h"


//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    Visualizer _visualizer;
    GuiSection<LevelGUI> _levelGUI;
    GuiSection<SaturatorGUI> _saturatorGUI;
    GuiSection<DelayGUI> _delayGUI;
    GuiSection<LowPassGUI> _lowPassGUI;
    GuiSection<CompressorGUI> _compressorGUI;
    GeneratorGUI _generatorGUI;
    juce::Slider _windowSeconds;
    juce::TextButton _toggleStuff;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
