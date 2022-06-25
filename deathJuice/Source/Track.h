/*
  ==============================================================================

    Track.h
    Created: 9 Mar 2022 4:38:44pm
    Author:  Angie Carola

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include <vector>
//#include <set>

class Track
{
    public:
        Track() = default;
        Track(juce::File _audioFile);

        /** dictates what == means between tracks 
        same fullPath*/
        bool operator==(const Track* other);

        //setters
        void setLength(double pos);
        void setNoName();
        void setValuesAfterFirstLoad(juce::String trackLenght, juce::String _textValueSuffix);
        
        //getters
        const double& getTrackLength();
        const juce::String& getTextValueSuffix();
        const juce::String& getTrackLengthString();
        const juce::String& getFileName();
        const juce::File& getAudioFile();
        void setTrackLengthString(juce::String );
        

        const juce::String fullPath;
    private:
        //juce::FileInputSource fileInputSource;
        juce::File audioFile;
        juce::String fileName;
        juce::String textValueSuffix;
        juce::String trackLengthString;
        double trackLength;


};
