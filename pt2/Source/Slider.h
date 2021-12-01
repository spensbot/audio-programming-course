/*
  ==============================================================================

    Slider.h
    Created: 6 Nov 2021 3:23:47pm
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Slider  : public juce::Slider
{
public:
    Slider() = default;
    
    juce::String getTextFromValue (double value) override
    {
        return juce::String::toDecimalStringWithSignificantFigures(value, 3) + getTextValueSuffix();
    }

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Slider)
};
