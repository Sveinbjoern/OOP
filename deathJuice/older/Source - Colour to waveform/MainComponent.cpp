#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    DBG("MainComponent::MainComponent" );
    audioFormatManager.registerBasicFormats();


    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    std::string formats;
    formats.append("Recognized formats are:\n");
    for (int i = 0; i < audioFormatManager.getNumKnownFormats(); i++) {
        std::string s = audioFormatManager.getKnownFormat(i)->getFormatName().toStdString();

        //DBG("MainComponent::MainComponent audio formats " << i << " " << s);
        formats.append(s);
        if (i != audioFormatManager.getNumKnownFormats() - 1)
            formats.append(", ");
    }
    formats.append("!");
    DBG("MainComponent::MainComponent audio formats " << formats);
    leftDeck.setformatsString(formats);
    rightDeck.setformatsString(formats);

    addAndMakeVisible(leftDeck);
    addAndMakeVisible(rightDeck);

    addAndMakeVisible(leftDeck.waveform);
    addAndMakeVisible(rightDeck.waveform);

    addAndMakeVisible(playlistComponent);

    playlistComponent.loadPlaylist();

    addAndMakeVisible(searchField);
    searchField.setTextToShowWhenEmpty(juce::String{ "<Enter search term>" }, juce::Colours::blanchedalmond);
    searchField.addListener(this);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    
    mixerAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    leftPlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
    rightPlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerAudioSource.addInputSource(&leftDeck.getSoundElement(), false);
    mixerAudioSource.addInputSource(&rightDeck.getSoundElement(), false);


}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // audio-processing code here!
    mixerAudioSource.getNextAudioBlock(bufferToFill);
    

    // We need to clear the buffer
    // to prevent the output of random noise 
    // if we are not producing any data
    //bufferToFill.clearActiveBufferRegion();
}



void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    //Do I need these. They can be called in their own lifecycle
    leftPlayer.releaseResources();
    rightPlayer.releaseResources();
    mixerAudioSource.releaseResources();


}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    int steps = 8;
    int width = getWidth();
    float halfWidth = width / 2;
    float heightStep = getHeight() / steps;
    float halfHeightStep = heightStep / 2;



    leftDeck.waveform.setBounds(0,0,width,halfHeightStep);
    rightDeck.waveform.setBounds(0, halfHeightStep, width, halfHeightStep);

    playlistComponent.setBounds(0, heightStep*6 , width, heightStep*2 );

    leftDeck.setBounds(0,heightStep,halfWidth, heightStep*5);
    rightDeck.setBounds(halfWidth, heightStep, halfWidth, heightStep * 5);

    //searchField.setBounds(0, heightStep*6, , halfWidth- halfWidth/8 );
    searchField.setBounds(0, heightStep * 5.70 , halfWidth*0.75, heightStep* 0.3125);
}



//==============================================================================
//Event functions
void MainComponent::buttonClicked(juce::Button* button)
{

    juce::String ID = button->getComponentID();
    int row = ID.getIntValue() / 10;
    int column = ID.getIntValue() % 10;
    

    if (column == 1)
    {
        //Play track on leftDeck
        leftDeck.addTrackIndexedToDeck(row);
        
        //DBG("button" << button);
    }
    else if (column == 5)
    {
        //Play track on rightDeck
        rightDeck.addTrackIndexedToDeck(row);

    }
    else if (column == 6)
    {
        //Remove from decks if neccessary
        leftDeck.removeCurrentTrack(row);
        rightDeck.removeCurrentTrack(row);
        //DBG("row" << row << "colum" << column);
        //Remove from playlist
        playlistComponent.deleteTrack(row);

        //DBG("MainComponent::buttonClicked delete button cliked on row " << row);
        //deleteTrack(row);
    }


    DBG("MainComponent::buttonClicked " << ID.getIntValue() / 10 << " " << ID.getIntValue() % 10);

}

void MainComponent::textEditorTextChanged(juce::TextEditor& editor)
{
    DBG("MainComponent::textEditorTextChanged");
    juce::String searchTerm = editor.getText();
    if (searchTerm != "")
    {
        playlistComponent.setSearchedTracks(searchTerm);
       
    }
    else
    {
        playlistComponent.setSearchedTracksToDefault();
        playlistComponent.tableListBoxUpdate();
    }
}
void MainComponent::textEditorEscapeKeyPressed(juce::TextEditor& editor)
{
    DBG("MainComponent::textEditorEscapeKeyPressed  " << editor.getText());
    editor.setText("");
    editor.giveAwayKeyboardFocus();
    playlistComponent.setSearchedTracksToDefault();
    playlistComponent.tableListBoxUpdate();
    
}