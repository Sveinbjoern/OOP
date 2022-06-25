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

        /** Necessary for the insert method of the std::vector<Track> tracks */
        //Track operator =(const Track&);
        //Track& operator=(Track&& other) noexcept;
        //bool operator==(const Track& other);
        bool operator==(const Track* other);

        //juce::FileInputSource& getFileInputSource();
        void setLength(double pos);
        void setValuesAfterFirstLoad(juce::String trackLenght, juce::String _textValueSuffix);
        //const juce::String& getFullPath();
        //static Track createTrack(const juce::File& _audioFile, std::set<juce::String>& setOfTracks);
        //static bool isInSet(const juce::File& _audioFile, const std::set<juce::String>& setOfTracks);

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
