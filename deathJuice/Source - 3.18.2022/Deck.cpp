/*
  ==============================================================================

    Deck.cpp
    Created: 6 Mar 2022 3:55:45pm
    Author:  

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Deck.h"


//==============================================================================
Deck::Deck(SoundElement& _soundElement,
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse,
        PlaylistComponent& _playlistComponent,
        bool _reverseLayout) :  soundElement( _soundElement),
                                reverseLayout(_reverseLayout),
                                waveform(formatManagerToUse, cacheToUse, _soundElement),
                                playlistComponent(_playlistComponent)
                                //currentTrack(Track{})
{
    DBG(" Deck::Deck: soundElement created ");

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //soundElement.prepareToPlay(420, 42.0);

    addAndMakeVisible(waveform);

    //Buttons setup
    addAndMakeVisible(playButton);
    playButton.addListener(this);
    playButton.setEnabled(false);


    addAndMakeVisible(stopButton);
    stopButton.addListener(this);
    stopButton.setEnabled(false);

    addAndMakeVisible(loadButton);
    loadButton.addListener(this);


    //Sliders setup
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.addListener(this);
    gainSlider.setRange(0.0f, 1.0f);
    gainSlider.setValue(0.5f);
    gainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox,true,0,0);
    //gainSlider.setTextBoxStyle()
    //gainSlider.setEnabled(false);
    soundElement.setGain(gainSlider.getValue());

    addAndMakeVisible(speedSlider);
    speedSlider.setTextBoxIsEditable(false);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    speedSlider.setRange(0.0f, 5.0f);
    speedSlider.setDoubleClickReturnValue(true, 1.0f);
    speedSlider.setValue(1.0f);
    speedSlider.setSkewFactorFromMidPoint(1);
    //speedSlider.setTextBoxIsEditable(false);
    speedSlider.addListener(this);
    speedSlider.setNumDecimalPlacesToDisplay(3);
    
    //TEMP
    //speedSlider.hideTextBox(true);
    //auto children = speedSlider.getChildren();
    

    addAndMakeVisible(posSlider);
    posSlider.setRange(0.0f, 1.0f);
    posSlider.addListener(this);
    posSlider.hideTextBox(true);
    posSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    posSlider.setNumDecimalPlacesToDisplay(1);
    posSlider.setColour(0, getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    addAndMakeVisible(vinyl);
    vinyl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    vinyl.setPopupMenuEnabled(true);
    vinyl.setRange(-2.0f, 2.0f);
    vinyl.setValue(0.0f);
    vinyl.addListener(this);
    vinyl.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    isPaused = true;


    startTimer(100);


}

Deck::~Deck()
{
    stopTimer();
}

void Deck::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
   //g.drawText ("Deck", getLocalBounds(),
   //            juce::Justification::centred, true);   // draw some placeholder text
}

void Deck::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..heightStep
    int steps = 8;

    float widthStep = getWidth() / steps;
    float heightStep = getHeight() / steps;

    float halfWidth = getWidth() / 2;
    float halfHeighStep = heightStep / 2;
    float buttonHeight = getHeight() - halfHeighStep;
    

    playButton.setBounds(halfWidth-widthStep*2,buttonHeight , widthStep, halfHeighStep);
    stopButton.setBounds(halfWidth-widthStep, buttonHeight, widthStep*2, halfHeighStep);
    loadButton.setBounds(halfWidth+ widthStep, buttonHeight, widthStep, halfHeighStep);

    if (reverseLayout)
    {
        speedSlider.setBounds(0, 0, widthStep, getHeight());
        gainSlider.setBounds(widthStep , heightStep, widthStep, getHeight()-heightStep);
        vinyl.setBounds(widthStep*2, heightStep, widthStep * (steps - 2), heightStep * (steps - 2));
        posSlider.setBounds(widthStep, 0, widthStep * (steps - 1), heightStep);
        //waveform.setBounds(widthStep, 0, widthStep * (steps - 1), heightStep);
    }
    else
    {
        gainSlider.setBounds(widthStep * (steps - 2),heightStep,widthStep,getHeight()-heightStep);
        speedSlider.setBounds(widthStep*(steps-1), 0, widthStep, getHeight());
        vinyl.setBounds(0, heightStep, widthStep * (steps - 2), heightStep * (steps - 2));
        posSlider.setBounds(0, 0, widthStep * (steps - 1), heightStep);
        //waveform.setBounds(0, 0, widthStep * (steps - 1), heightStep);
    }

    

}


//=================================================================================================
//Seters and getters
void Deck::setformatsString(std::string s)
{
    formats = s;
}

//Audio functions

SoundElement& Deck::getSoundElement()
{
    return soundElement;
}

//===================================================================================================
//Event management

void Deck::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    { 
        //DBG(" Deck::buttonClicked: They clicked the play button ");
        playDeck();
    }
    else if (button == &stopButton)
    {
        if (isPaused)
            stopDeck();
        else
            pauseDeck();
        //DBG(" Deck::buttonClicked: They clicked the stop button ");
        //soundElement.stop();
    }
    else if (button == &loadButton)
    {
        DBG(" Deck::buttonClicked: They clicked the load button ");

        juce::FileChooser chooser{ "Select a sound file to play..." };

        if (chooser.browseForFileToOpen())
        {
            // Use the check for a valid file in SoundElement::loadFile to decide if we
            // continue with other loading functions
            if (soundElement.loadFile(chooser.getResult()))
            {


                //    DBG("Loadbutton chooser.getResult");
                if (playlistComponent.addToSetOfTracks(chooser.getResult()))
                    addNewTrack(chooser.getResult());

                setDeckAfterLoadingTrack(playlistComponent.getTrack(chooser.getResult()));

            }
            else
                alertFILE_TYPE();

            
            
        }
        //loadURL(juce::URL{ chooser.getResult() });
        //juce::FileChooser chooser{ "Select a file..." };
        //if (chooser.browseForFileToOpen())
        //{
        //    soundElement.loadURL(juce::URL{ chooser.getResult() });
        //    //waveformDisplay.loadURL(URL{ chooser.getResult() });
        //
        //}
    }
}


//==================================================================================================
//Alerts

void Deck::alertFILE_TYPE()
{
    juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
        "Not a known audioFormat:",
        formats,
        "OK"
    );
}


void Deck::reafirmTrackInfo()
{

}


void Deck::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        soundElement.setGain(slider->getValue() );
        
    }

    if (slider == &speedSlider)
    {
        soundElement.setSpeed(slider->getValue()+ vinyl.getValue());
    }

    if (slider == &posSlider)
    {
        soundElement.setPosition(slider->getValue());
    }
    if (slider == &vinyl)
    {
        soundElement.setSpeed(slider->getValue()+ gainSlider.getValue());
    }
}

void Deck::setDeckAfterLoadingTrack( Track& track)
{
    posSlider.setRange(0.0, soundElement.getTrackLength());
    posSlider.setValue(0.0);
    
    posSlider.setTextValueSuffix(track.getTextValueSuffix());
    posSlider.setNumDecimalPlacesToDisplay(1);

    currentTrack = &track;

    waveform.loadFile(track.fullPath);

    playDeck();
}

void Deck::addNewTrack(juce::File& audioFile)
{
    DBG("Loadbutton old track");
    //DBG("Loadbutton track.fullPath" << track.fullPath);
    Track track = Track{ audioFile };
    double trackLenght = soundElement.getTrackLength();
    juce::String trackLengthString{ trackLenght , 1 };
    juce::String stringToAdd{ "/" };
    stringToAdd.append(trackLengthString, 10);
    stringToAdd.append(" s", 2);

    track.setValuesAfterFirstLoad(trackLengthString, stringToAdd);
    DBG("Deck::addNewTrack newTrack.fullPath" << track.fullPath);
    DBG("Deck::addNewTrack getLength" << track.getTrackLengthString());
    playlistComponent.addTrack(track);
    playlistComponent.saveToPlaylist(track);
    
    playlistComponent.tableListBoxUpdate();

    //track.setValuesAfterFirstLoad(trackLenght, stringToAdd);
}

void Deck::setDeckAfterLoadingNewTrack( juce::File& audioFile)
{
    //Track& track(playlistComponent.addTrack(audioFile));
    //DBG("Loadbutton new track");
    //double trackLength = soundElement.getTrackLength();
    //
    //posSlider.setRange(0.0, trackLength);
    //posSlider.setValue(0.0);
    //juce::String stringToAdd{ "/" };
    //juce::String extraString{ soundElement.getTrackLength(), 1 };
    //extraString.append(" s", 2);
    //stringToAdd.append(extraString,10);
    //posSlider.setTextValueSuffix(stringToAdd);
    //posSlider.setNumDecimalPlacesToDisplay(1);
    //
    //track.setValuesAfterFirstLoad(trackLength, stringToAdd);
    
}




//Timer functions
void Deck::timerCallback()
{
    //WAIT
    //DBG(" Deck::timerCallBack:  ");
    
    waveform.setPositionRelative(
        soundElement.getPositionRelative());

    posSlider.setValue(soundElement.getPosition(),juce::dontSendNotification);


}


// Drag and drop functions
bool Deck::isInterestedInFileDrag(const juce::StringArray& files)
{
    
    return true;
}

void Deck::filesDropped(const juce::StringArray& files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        juce::File audioFile{ files[0] };
        //playlistComponent.isInSetOfTracks()
        if (soundElement.loadFile(audioFile))
        {
            if (playlistComponent.addToSetOfTracks(audioFile))
                addNewTrack(audioFile);

            setDeckAfterLoadingTrack(playlistComponent.getTrack(audioFile));
        }
        else
            alertFILE_TYPE();
       
    }
}

void Deck::addTrackIndexedToDeck(int trackNumber)
{
    Track& track = playlistComponent.getTrack(trackNumber);
    if (soundElement.loadFile(track.fullPath))
    {
        setDeckAfterLoadingTrack(track);
    }
    else
        alertFILE_TYPE();

}

void Deck::removeCurrentTrack(int trackNumber)
{
    Track& track = playlistComponent.getTrack(trackNumber);
    if (&track == currentTrack)
    {
        DBG("Deck::RemoveCurrentTrack We have a hit");
        resetDeck();
    }
        
    DBG("Deck::RemoveCurrentTrack ");
    
    //alertFILE_TYPE();

}




//=================================================================================
//State controls

void Deck::pauseDeck()
{
    playButton.setEnabled(true);
    soundElement.stop();
    isPaused = true;
}
void Deck::stopDeck()
{
    soundElement.stop();
    stopButton.setEnabled(false);
    posSlider.setValue(0.0); 
    isPaused = false;

}

void Deck::resetDeck()
{
    stopDeck();
    currentTrack = nullptr;
    //soundElement.releaseResources();
    waveform.resetFileLoaded();
    posSlider.setRange(0.0, 0.1);
    posSlider.setTextValueSuffix("");
    posSlider.setNumDecimalPlacesToDisplay(1);
    playButton.setEnabled(false);


}

void Deck::playDeck()
{
    soundElement.start();
    isPaused = false;
    stopButton.setEnabled(true);
    playButton.setEnabled(false);


}