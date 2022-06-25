#pragma once

#include <JuceHeader.h>
#include "Deck.h"
#include "SoundElement.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  :  public juce::AudioAppComponent,
                        public juce::Button::Listener,
                        public juce::TextEditor::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

    //==============================================================================
    //event functions
    void buttonClicked(juce::Button* button) override;
    void textEditorTextChanged(juce::TextEditor&)override;
    void textEditorEscapeKeyPressed(juce::TextEditor&) override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    juce::TextEditor searchField;

    juce::AudioFormatManager audioFormatManager;
    juce::MixerAudioSource mixerAudioSource;
    juce:: AudioThumbnailCache audioThumbnailCache{ 100 };

    SoundElement leftPlayer{ audioFormatManager };
    SoundElement rightPlayer{ audioFormatManager };

    PlaylistComponent playlistComponent{this};

    Deck leftDeck{  leftPlayer, audioFormatManager, audioThumbnailCache, playlistComponent, false , juce::Colour(25,49,255)};
    Deck rightDeck{  rightPlayer, audioFormatManager, audioThumbnailCache , playlistComponent, true,juce::Colour(255,49,23)  };




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
