/*
  ==============================================================================

    GuiSection.h
    Created: 31 Oct 2021 1:32:06pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

template <typename Contents>
class GuiSection  : public juce::Component
{
public:
    GuiSection(juce::String title, std::unique_ptr<Contents> contents) : _contents(std::move(contents))
    {
        addAndMakeVisible(&_title);
        _title.setText(title, juce::NotificationType::dontSendNotification);
        _title.setFont(juce::Font(30.f));
        addAndMakeVisible(_contents.get());
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::grey);   // clear the background
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        _title.setBounds(bounds.removeFromTop(30));
        _contents->setBounds(bounds);
    }

private:
    juce::Label _title;
    std::unique_ptr<Contents> _contents;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiSection)
};
