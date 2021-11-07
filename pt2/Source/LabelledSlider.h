/*
  ==============================================================================

    LabelledSlider.h
    Created: 6 Nov 2021 3:30:02pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <optional>

#include "Slider.h"

//==============================================================================
/*
*/
class LabelledSlider  : public juce::Component
{
public:
    struct Options {
        std::function<void(float)> onChange;
        std::optional<float> skewMidpoint;
        std::optional<juce::String> label;
        std::optional<juce::String> suffix;
        float min = 0.f;
        float max = 1.f;
        float init = 0.f;
    };
    
    LabelledSlider() = default;
    
    void setup(Options options) {
        addAndMakeVisible(_slider);
        _slider.setRange(options.min, options.max);
        _slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        if (options.skewMidpoint) _slider.setSkewFactorFromMidPoint(*options.skewMidpoint);
        if (options.suffix) _slider.setTextValueSuffix(*options.suffix);
        _slider.onValueChange = [this, options]{ options.onChange(_slider.getValue()); };
        _slider.setValue(options.init);
        _slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
        
        if (options.label) {
            _label.emplace();
            addAndMakeVisible(*_label);
            _label->setFont(juce::Font(18.f));
            _label->setText(*options.label, juce::NotificationType::dontSendNotification);
            _label->setJustificationType(juce::Justification::centred);
        }
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        
        if (_label) {
            _label->setBounds(bounds.removeFromTop(30));
            bounds.removeFromTop(10);
        }
        _slider.setBounds(bounds);
    }

private:
    Slider _slider;
    std::optional<juce::Label> _label;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelledSlider)
};
