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


    // Memeber that allow outside managment of the audio
    void loadURL(juce::URL audioURL);
    bool loadFile(juce::File audioFile);

    bool checkFileStatic(juce::File audioFile);
    
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);
    void start();
    void stop();


    /** get the relative position of the playhead */
    double getPositionRelative();

    double getPosition();
    double getTrackLength();

private:
    juce::AudioFormatManager& audioFormatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> audioFormatReaderSource;
    juce::AudioTransportSource audioTransportSource;
    juce::ResamplingAudioSource resamplingAudioSource{ &audioTransportSource, false, 2 };

};
