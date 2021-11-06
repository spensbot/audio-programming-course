#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    initSlider(m_sliderHz, m_labelHz, "Frequency");
    m_sliderHz.setTextValueSuffix(" Hz");
    m_sliderHz.setRange(settings::FREQUENCY_MIN, settings::FREQUENCY_MAX);
    m_sliderHz.setSkewFactor(0.5);
    m_sliderHz.setValue(m_hz);
    m_sliderHz.setNumDecimalPlacesToDisplay(2);
    m_sliderHz.onValueChange = [this](){
        m_hz = m_sliderHz.getValue();
        updateVisualizer();
    };
    
    addAndMakeVisible(m_visualizer);
    updateVisualizer();
    
    addAndMakeVisible(m_sliderVisualizerSampleRate);
    m_sliderVisualizerSampleRate.setTextValueSuffix(" Hz");
    m_sliderVisualizerSampleRate.setValue(m_visualizerSampleRate);
    m_sliderVisualizerSampleRate.setRange(settings::SAMPLE_RATE_MIN, settings::SAMPLE_RATE_MAX);
    m_sliderVisualizerSampleRate.setSkewFactor(0.5);
    m_sliderVisualizerSampleRate.setNumDecimalPlacesToDisplay(2);
    m_sliderVisualizerSampleRate.onValueChange = [this]{
        m_visualizerSampleRate = m_sliderVisualizerSampleRate.getValue();
        updateVisualizer();
    };
    
    addAndMakeVisible(m_buttonUpOctave);
    m_buttonUpOctave.setButtonText("Up Octave");
    m_buttonUpOctave.onClick = [this] {
        m_hz = m_hz * 2.0;
        m_sliderHz.setValue(m_hz);
    };
    
    addAndMakeVisible(m_buttonDownOctave);
    m_buttonDownOctave.setButtonText("Down Octave");
    m_buttonDownOctave.onClick = [this]{
        m_hz = m_hz / 2.0;
        m_sliderHz.setValue(m_hz);
    };
    
    addAndMakeVisible(m_buttonToggleSamples);
    m_buttonToggleSamples.setButtonText("Samples");
    m_buttonToggleSamples.setToggleState(false, juce::NotificationType::dontSendNotification);
    m_buttonToggleSamples.onClick = [this]{
        m_buttonToggleSamples.setToggleState(!m_buttonToggleSamples.getToggleState(), juce::NotificationType::dontSendNotification);
        updateVisualizer();
    };
    
    addAndMakeVisible(m_buttonToggleWave);
    m_buttonToggleWave.setButtonText("Wave Shape");
    m_buttonToggleWave.setToggleState(true, juce::NotificationType::dontSendNotification);
    m_buttonToggleWave.onClick = [this]{
        m_buttonToggleWave.setToggleState(!m_buttonToggleWave.getToggleState(), juce::NotificationType::dontSendNotification);
        updateVisualizer();
    };
    
    addAndMakeVisible(m_labelSecondsStart);
    m_labelSecondsStart.setText("0.0 (s)", juce::NotificationType::dontSendNotification);
    m_labelSecondsStart.setColour (juce::Label::backgroundColourId, juce::Colour(0.0f, 0.0f, 0.0f, 0.8f));
    m_labelSecondsStart.setJustificationType(juce::Justification::centredLeft);
    
    addAndMakeVisible(m_labelSecondsEnd);
    m_labelSecondsEnd.setText(juce::String::toDecimalStringWithSignificantFigures(settings::WINDOW_SECONDS, 1) + " (s)", juce::NotificationType::dontSendNotification);
    m_labelSecondsEnd.setColour (juce::Label::backgroundColourId, juce::Colour(0.0f, 0.0f, 0.0f, 0.8f));
    m_labelSecondsEnd.setJustificationType(juce::Justification::centredRight);
    
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    log("Samples Per Block", samplesPerBlockExpected);
    log("Sample Rate", sampleRate);
    m_sampleRate = sampleRate;
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    const auto HEIGHT = 40;
    const auto WIDTH = 100;
    
    auto bounds = getLocalBounds();
    auto frequencyBounds = bounds.removeFromTop(HEIGHT);
    m_buttonDownOctave.setBounds(frequencyBounds.removeFromLeft(WIDTH));
    m_buttonUpOctave.setBounds(frequencyBounds.removeFromLeft(WIDTH));
    m_sliderHz.setBounds(frequencyBounds);
//    m_sliderLevel.setBounds(bounds.removeFromTop(50));
    
    auto sampleRateBounds = bounds.removeFromBottom(HEIGHT);
    m_buttonToggleWave.setBounds(sampleRateBounds.removeFromLeft(WIDTH));
    m_buttonToggleSamples.setBounds(sampleRateBounds.removeFromLeft(WIDTH));
    m_sliderVisualizerSampleRate.setBounds(sampleRateBounds);
    m_visualizer.setBounds(bounds);
    
    auto deltaY = (bounds.getHeight() - 30) / 2;
    m_labelSecondsStart.setBounds(bounds.removeFromLeft(50).reduced(0, deltaY));
    m_labelSecondsEnd.setBounds(bounds.removeFromRight(60).reduced(0, deltaY));
}
