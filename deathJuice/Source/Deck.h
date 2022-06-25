/*
  ==============================================================================

    Deck.h
    Created: 6 Mar 2022 3:55:45pm
    Author:  Angie Carola

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundElement.h"
#include "Waveform.h"
#include "PlaylistComponent.h"
#include "Vinyl.h"


//==============================================================================
/*
 *   The Deck class creates everything needed for a deck, it handles GUI
 *   itself and has a SoundElement and WaveformDisplays stored as references.
 *   Inciated with:    
 *      juce::AudioFormatManager&
 *      juce::AudioThumbnailCache&
 *      bool reverseLayout: this bool decides if the layout is fitted to the 
 *                          left or right of the side of the app by reversing the layout.
*/
class Deck : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer,
    public juce::FileDragAndDropTarget
{
public:

    /** Constructor that creates the Deck*/
    Deck(   SoundElement& _soundElement,
            juce::AudioFormatManager& formatManagerToUse,
            juce::AudioThumbnailCache& cacheToUse,
            PlaylistComponent& _playlistComponent,
            bool _reverseLayout,
            juce::Colour _deckColour);
    ~Deck() override;

    //==========================================================
    //juce functions
    void paint (juce::Graphics&) override;
    void resized() override;
    /** What to do when the callback of the timer comes*/
    void timerCallback()override;
    /** implement Button::Listener */
    void buttonClicked(juce::Button* button) override;

    /** implement Slider::Listener */
    void sliderValueChanged(juce::Slider* slider) override;

    /**functions for dragand drop functionality*/
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    /**functions for dragand drop functionality*/
    void filesDropped(const juce::StringArray& files, int x, int y) override;


   
    /** adds an existing track to the deck*/
    void addTrackIndexedToDeck(int trackNumber);
    /** checks if the current track is one that is being deleted
    and removes it and resets the track if it is the case*/
    void removeCurrentTrack(int trackNumber);
    /**SoundElements */
    SoundElement& getSoundElement();

    /** set the string that is used to display known formats*/
    void setformatsString(std::string);



    Waveform waveform;
   
    //Deck controls
    void Deck::pauseDeck();
    void Deck::stopDeck();
    void Deck::resetDeck();
    void Deck::playDeck();
private:
    
    int heightSteps;
    int widthSteps;
    bool reverseLayout;
    bool isPaused;
    juce::Colour deckColour;

    bool soundElementHasBeenSent;

    SoundElement& soundElement;
    PlaylistComponent& playlistComponent;
    Vinyl vinyl;

    void setDeckAfterLoadingTrack( Track* track);
    void setDeckAfterLoadingNewTrack( juce::File& audioFile );
    void addNewTrack(juce::File& audioFile);
    void reafirmTrackInfo();
    void alertFILE_TYPE();

    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP/PAUSE" };
    juce::TextButton loadButton{ "LOAD" };
    
    juce::Label gainLabel;
    juce::Slider gainSlider;
    juce::Label speedLabel;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    Track* currentTrack;

    std::string formats;


 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Deck)
};
