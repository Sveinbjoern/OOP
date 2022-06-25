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

    //DBG("Track::Track trackLength: " << trackLength);
    //DBG("Track::Track textValueSuffix: " << textValueSuffix);
    //DBG("Track::Track trackLengthString: " << trackLength);
    

}

//Track Track::createTrack(const juce::File& _audioFile, std::set<juce::String>& setOfTracks)
//{
//
//
//    
//        return Track(_audioFile);
//    
//    
//}



void Track::setLength(double pos)
{
    trackLength = pos;
}

void Track::setValuesAfterFirstLoad(juce::String _trackLength, juce::String _textValueSuffix)
{
    //DBG("Track::setValueAfterFirstLoad _trackLenght" << _trackLength);
    //trackLength = _trackLength;
    //DBG("Track::setValueAfterFirstLoad _trackLenght: " << _trackLength);
    //DBG("Track::setValueAfterFirstLoad _textValueSuffix: " << _textValueSuffix);
    //DBG("Track::setValueAfterFirstLoad textValueSuffix: " << textValueSuffix);
    //DBG("Track::setValueAfterFirstLoad trackLenght: " << trackLength);
    //trackLengthString = *new juce::String(_trackLength);
    trackLengthString = _trackLength;
    textValueSuffix = juce::String{_textValueSuffix};
    //DBG("Track::setValueAfterFirstLoad trackLenght: " << trackLength);
    //DBG("Track::setValueAfterFirstLoad textValueSuffix: " << textValueSuffix);

    //textValueSuffix = *new juce::String(_textValueSuffix);
    //textValueSuffix.clear();
    
    //trackLengthString.append( _trackLength , 10 );
    
    //DBG("Track::setValueAfterFirstLoad trackLenghtString" << trackLengthString.toStdString());

    //textValueSuffix = _textValueSuffix;
    //DBG("Track::setValueAfterFirstLoad textValueSuffix" << textValueSuffix.toStdString());
    //trackLength = std::stod( trackLengthString.toStdString() );

}


//bool Track::isInSet(const juce::File& audioFile, const std::set<juce::String>& setOfTracks)
//{
//    bool isIn = setOfTracks.find(audioFile.getFullPathName()) != setOfTracks.end();
//    std::string dbg = (isIn ? "YES" : "NO");
//    DBG("Track::isInSet track found " << dbg);
//    return setOfTracks.find(audioFile.getFullPathName()) != setOfTracks.end();
//    
//
//}

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

//juce::String Track::getFullPath()
//{
//    return fullPath;
//}

//void Track::operator =(const Track& track)
//{
//    DBG("Track::operator incomming track " << track.fullPath);
//    DBG("Track::operator outgoing track " << this->fullPath);
//    track = this;
//}





Track Track::operator=(const Track& other)
{
    // Guard self assignment
    if (this == &other)
        return *this;
    
    
    DBG("Track::operator= this.fullPath "<< this->fullPath);
    Track newTrack{other.audioFile};
    newTrack.setValuesAfterFirstLoad(other.trackLengthString,other.textValueSuffix);

    DBG("Track::operator= newTrack.fullPath " << newTrack.fullPath);
    
    return newTrack;
}

bool Track::operator==(const Track& other)
{
    
    return this->fullPath == other.fullPath;

}

bool Track::operator==(const Track* other)
{

    return this == other;

}


// move assignment
//Track& Track::operator=(Track&& other) noexcept
//{
//    // Guard self assignment
//    if (this == &other)
//        return *this; // delete[]/size=0 would also be ok
//
//    delete[] mArray;                               // release resource in *this
//    mArray = std::exchange(other.mArray, nullptr); // leave other in valid state
//    size = std::exchange(other.size, 0);
//    return *this;
//}
