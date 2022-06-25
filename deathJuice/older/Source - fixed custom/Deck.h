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

    void paint (juce::Graphics&) override;
    void resized() override;

    
    SoundElement& getSoundElement();

    /** activate the prepareToPlay of the soundSource */
   
    void addTrackIndexedToDeck(int trackNumber);
    void removeCurrentTrack(int trackNumber);

    void timerCallback()override;
  
    void setformatsString(std::string);

    /** implement Button::Listener */
    void buttonClicked(juce::Button* button) override;

    /** implement Slider::Listener */
    void sliderValueChanged(juce::Slider* slider) override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

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

    SoundElement& soundElement;

    PlaylistComponent& playlistComponent;

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
    //juce::Slider vinyl;

    Track* currentTrack;

    std::string formats;


    Vinyl vinyl;
    //juce::AudioFormatManager audioFormatManager;
    //juce::AudioThumbnailCache audioThumbnailCache;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Deck)
};
