#pragma once

#include <JuceHeader.h>
#include "Visualizer.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
    
    void initSlider(juce::Slider& slider, juce::Label& label, const std::string& labelText) {
        addAndMakeVisible(&slider);
        addAndMakeVisible(&label);
        label.attachToComponent(&slider, true);
        label.setText(labelText, juce::NotificationType::dontSendNotification);
    }
    
    template <typename T>
    void log(const std::string& message, T var) {
        log(message + " = " + std::to_string(var));
    }
    
    void log(const std::string& message) {
        juce::Logger::getCurrentLogger()->writeToLog ("asdf: " + message);
    }
    
    void updateVisualizer() {
        bool drawWave = m_buttonToggleWave.getToggleState();
        bool drawSamples = m_buttonToggleSamples.getToggleState();
        m_visualizer.reset(m_level, m_hz, drawWave, drawSamples ? std::make_optional(m_visualizerSampleRate) : std::nullopt);
    }
    
    //==============================================================================
    
    juce::Random m_random;
    double m_hz = settings::FREQUENCY_MIN;
    const double m_level = 0.8;
    double m_sampleRate = 0.0;
    double m_visualizerSampleRate = settings::SAMPLE_RATE_MIN;
    
    juce::Slider m_sliderHz;
    juce::Slider m_sliderVisualizerSampleRate;
    juce::Label m_labelHz;
    juce::Label m_labelVisualizerSampleRate;
    juce::TextButton m_buttonUpOctave;
    juce::TextButton m_buttonDownOctave;
    juce::TextButton m_buttonToggleSamples;
    juce::TextButton m_buttonToggleWave;
    juce::Label m_labelSecondsStart;
    juce::Label m_labelSecondsEnd;
    
    Visualizer m_visualizer;
    
    double m_sinPos_radians = 0.0;
    
    
    
    
    
    
    
    
    
    
    
    
    
public:
    
    
    
    
    
    
    
    
    
    
    
    
    // NOISE GENERATOR
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        // This function is called by the sound card's audio callback on a high priority "audio thread"
        // Expects you to fill the buffer with floats from -1.0 to 1.0
        
        auto& outBuffer = *bufferToFill.buffer;
        
        for (auto sampleIndex=0 ; sampleIndex<bufferToFill.numSamples ; ++sampleIndex) {
            
            float value;
            
            // VARIABLE SIN GENERATOR
            value = std::sin(m_sinPos_radians);
            const auto hz = m_hz; // oscillations / second
            const auto sampleRate = m_sampleRate; // samples / second  (44100)
            const auto twoPi = juce::MathConstants<double>::twoPi; // radians / oscillation
            
//            auto radiansPerSecond = twoPi * hz;
//            auto radiansPerSample = radiansPerSecond / sampleRate;
            
            m_sinPos_radians += hz * twoPi / sampleRate;

            // Set channel 0 & 1 (L & R) to value
            outBuffer.setSample(0, sampleIndex, value);
            outBuffer.setSample(1, sampleIndex, value);
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        // This function is called by the sound card's audio callback on a high priority "audio thread"
        // Expects you to fill the buffer with floats from -1.0 to 1.0
        
        auto& outBuffer = *bufferToFill.buffer;
        
        for (auto sample=0 ; sample<bufferToFill.numSamples ; ++sample) {
            
            float value;
            
            // NOISE GENERATOR
            value = m_random.nextFloat() * 0.2 - 0.1;
            
            // FIXED SIN GENERATOR
            value = std::sin(m_sinPos_radians);
            m_sinPos_radians += ;
            
            // VARIABLE SIN GENERATOR
            value = std::sin(m_sinPos_radians);
            const auto hz = m_hz; // oscillations / second
            const auto sampleRate = m_sampleRate; // samples / second  (44100)
            const auto twoPi = juce::MathConstants<double>::twoPi; // radians / oscillation

            auto radiansPerSecond = twoPi * hz;
            auto radiansPerSample = radiansPerSecond / sampleRate;

            // radians / sample
            m_sinPos_radians += radiansPerSample;
            
            // Set channel 0 & 1 (L & R) to value
            outBuffer.setSample(0, sample, value);
            outBuffer.setSample(1, sample, value);
        }
    }
    */
};
