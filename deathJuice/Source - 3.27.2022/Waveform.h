/*
  ==============================================================================

    Waveform.h
    Created: 8 Mar 2022 3:24:12pm
    Author:  Angie Carola

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundElement.h"

//==============================================================================
/*
*/
class Waveform :        public juce::Component,
                        public juce::ChangeListener,
    public juce::MouseListener
{

public:
    Waveform(juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse,
        SoundElement& _soundElement);
    ~Waveform() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;


    void loadURL(juce::URL audioURL);
    void loadFile(juce::File audioFile);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);

    void resetFileLoaded();

    void  mouseDown(const juce::MouseEvent& event) override;
    void  mouseDrag(const juce::MouseEvent& event) override;



private:

    SoundElement& soundElement;
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waveform)
};
