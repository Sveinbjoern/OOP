/*
  ==============================================================================

    SoundElement.h
    Created: 3 Mar 2022 11:25:29pm
    Author:  Angie Carola

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>





class SoundElement : public juce::AudioSource
{
public:
    
    SoundElement(juce::AudioFormatManager& _formatManager);
    ~SoundElement();


    // Member functions for creating audio
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;


    /** no longer in use loads file with an URL*/
    void loadURL(juce::URL audioURL);
    /** loads an audio file with an juce::File*/
    bool loadFile(juce::File audioFile);
    
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);
    void start();
    void stop();


    /** get the relative position of the playhead */
    double getPositionRelative();
    /** get the position in seconds of the playhead */
    double getPosition();
    /** get the length of the track in seconds */
    double getTrackLength();

private:
    juce::AudioFormatManager& audioFormatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> audioFormatReaderSource;
    juce::AudioTransportSource audioTransportSource;
    juce::ResamplingAudioSource resamplingAudioSource{ &audioTransportSource, false, 2 };

};
