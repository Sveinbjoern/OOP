/*
  ==============================================================================

    PlaylistComponent.h
    Created: 9 Mar 2022 4:03:40pm
    Author:  Me

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <set>
//#include <vector>
#include <fstream>
#include "Track.h"

//==============================================================================
/*
*/
class PlaylistComponent  :  public juce::Component,
                            public juce::TableListBoxModel,
                            public juce::Button::Listener
{
public:
    PlaylistComponent(juce::Button::Listener* _ButtonListner);
    ~PlaylistComponent() override;

    bool addToSetOfTracks( const juce::File& audioTrack);
    Track& addTrack(Track& track);
    Track& getTrack( juce::File& audioFile);
    Track& getTrack(int index);

    void deleteTrack(int index);


    //Filemanagement
    void saveToPlaylist(Track& track);
    void loadPlaylist();
    //void deleteTrack(int);


    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelcted, juce::Component* exisitingComponentToUpdate ) override;

    void tableListBoxUpdate();

    void buttonClicked(juce::Button* button)override;
private:

    //Deck* leftDeck = nullptr;
    //Deck* rightDeck = nullptr;

    int binarySearch(int& start, int& end, int& Current,  juce::String& fullPath);
    int getNumRows() override;
    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    juce::Button::Listener* mainComponentButtonListener;

    /**
    * Sort and add track to the tracks vector sorted by alphabetical order of full path name
    */
    void addTracks(const juce::StringArray& s);
    /**
    * Set of juce::Strings keeps an overview of what tracks we already have in the playlist
    */ 
    std::set<juce::String> setOfTracks;
    /** 
    *All track information stored in one container of Track objects
    */
    std::vector<Track> tracks;
    std::vector<int> ints;

    // The table list box is inherited from juce and gives a very functional and working table
    juce::TableListBox tableListBox;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)

};
