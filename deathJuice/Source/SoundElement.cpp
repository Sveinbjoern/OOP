/*
  ==============================================================================

    SoundElement.cpp
    Created: 3 Mar 2022 11:25:29pm
    Author:  Me

  ==============================================================================
*/

#include "SoundElement.h"



SoundElement::SoundElement(juce::AudioFormatManager& _formatManager):
    audioFormatManager(_formatManager)
{
    
    //DBG("SoundElement::SoundElement number of audio formats " << audioFormatManager.getNumKnownFormats());
    //for (int i = 0; i < audioFormatManager.getNumKnownFormats(); i++) {
    //    std::string s = audioFormatManager.getKnownFormat(i)->getFormatName().toStdString();
    //
    //    DBG("SoundElement::SoundElement audio formats " << i << " " << s);
    //}

}

SoundElement::~SoundElement()
{
}


void SoundElement::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    //DBG("SoundElement::prepareToPlay number of audio formats " << audioFormatManager.getNumKnownFormats());
    audioTransportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resamplingAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void SoundElement::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

    resamplingAudioSource.getNextAudioBlock(bufferToFill);
}
void SoundElement::releaseResources()
{
    audioTransportSource.releaseResources();
    resamplingAudioSource.releaseResources();
}

void SoundElement::loadURL(juce::URL audioURL)      
{
    //DBG("SoundElement::loadURL number of audio formats " << audioFormatManager.getNumKnownFormats());
    auto* reader = audioFormatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader,
            true));
        audioTransportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        audioFormatReaderSource.reset(newSource.release());
    }
}

bool SoundElement::loadFile(juce::File audioFile)
{
    //DBG("SoundElement::loadFile number of audio formats " << audioFormatManager.getNumKnownFormats());
    auto* reader = audioFormatManager.createReaderFor(audioFile.createInputStream());
    //DBG("SoundElement::loadFile reader->sampleRate " << reader->sampleRate );
    if (reader != nullptr) // good file!
    {
        //DBG("SoundElement::loadFile if true " );
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader,
            true));
        newSource->setLooping(true);
        audioTransportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        audioFormatReaderSource.reset(newSource.release());
        return true;
    }
    return false;
}


void SoundElement::setGain(double gain)             {
    DBG("SoundElement::setGain gain set to " << gain);
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        audioTransportSource.setGain(gain);
    }
}
void SoundElement::setSpeed(double ratio)           {
    if (ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else {
        resamplingAudioSource.setResamplingRatio(ratio);
    }
}
void SoundElement::setPosition(double posInSecs)    {
    audioTransportSource.setPosition(posInSecs);
}
void SoundElement::setPositionRelative(double pos)  {
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = audioTransportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}
void SoundElement::start()                          
{
    audioTransportSource.start();
}
void SoundElement::stop()                           
{
    audioTransportSource.stop();
}

double SoundElement::getPosition()
{
    return audioTransportSource.getCurrentPosition();
}

double SoundElement::getTrackLength()
{
    return audioTransportSource.getLengthInSeconds();
}

double SoundElement::getPositionRelative()
{
    if (audioTransportSource.getLengthInSeconds() == 0)
        return 0.0;
    
    return audioTransportSource.getCurrentPosition() / audioTransportSource.getLengthInSeconds();
    

}

