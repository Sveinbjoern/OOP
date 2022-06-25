/*
  ==============================================================================

    Track.cpp
    Created: 9 Mar 2022 4:38:44pm
    Author:  Me

  ==============================================================================
*/

#include "Track.h"
// The private constructor of the Track is only used by the static createTrackFunciton.
Track::Track( juce::File _audioFile):
    audioFile(_audioFile),
    fullPath(_audioFile.getFullPathName()),
    fileName(_audioFile.getFileNameWithoutExtension()),
    trackLength(0.0)
{
}

void Track::setLength(double pos)
{
    trackLength = pos;
}

void Track::setValuesAfterFirstLoad(juce::String _trackLength, juce::String _textValueSuffix)
{
    trackLengthString = _trackLength;
    textValueSuffix = juce::String{_textValueSuffix};
}


void Track::setTrackLengthString(juce::String trackLength)
{
    DBG("Track::setTRackLEngth incomming value " << trackLength.toStdString());
    //trackLengthString.replace(trackLengthString, trackLength);
    //trackLengthString.append(trackLength,10);
    DBG("Track::setTRackLEngth setValue " << trackLengthString.toStdString());
}

const double& Track::getTrackLength()
{
    return trackLength;
}

const juce::String& Track::getTrackLengthString()
{
    return trackLengthString;
}
const juce::String& Track::getTextValueSuffix()
{
    return textValueSuffix;
}



const juce::String& Track::getFileName()
{
    return fileName;
}

const juce::File& Track::getAudioFile()
{
    return audioFile;
}

bool Track::operator==(const Track* other)
{
    return this->fullPath == other->fullPath;
}


