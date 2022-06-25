/*
  ==============================================================================

    Waveform.cpp
    Created: 8 Mar 2022 3:24:12pm
    Author:  Angie Carola

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Waveform.h"

//==============================================================================
Waveform::Waveform(juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse,
    SoundElement& _soundElement) :
    audioThumb(1000, formatManagerToUse, cacheToUse),
    fileLoaded(false),
    position(0),
    soundElement (_soundElement)


{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    audioThumb.addChangeListener(this);

}

Waveform::~Waveform()
{
}

void Waveform::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour(juce::Colours::grey);
    //g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::orange);
    if (fileLoaded)
    {
        audioThumb.drawChannel(g,
            getLocalBounds(),
            0,
            audioThumb.getTotalLength(),
            0,
            1.0f
        );
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(position * getWidth()-1, 0, 3, getHeight());
    }
    else
    {
        g.setFont(30.0f);
        g.drawText("File not loaded...", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text

    }

   //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
   //
   //g.setColour (juce::Colours::grey);
   //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
   //
   //g.setColour (juce::Colours::white);
   //g.setFont (14.0f);
   //g.drawText ("Waveform", getLocalBounds(),
   //            juce::Justification::centred, true);   // draw some placeholder text
}

void Waveform::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


void Waveform::loadURL(juce::URL audioURL)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        repaint();
    }
}

void Waveform::loadFile(juce::File audioFile)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::FileInputSource(audioFile));
    if (fileLoaded)
    {
        repaint();
    }
}

void Waveform::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();

}

void Waveform::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}


void  Waveform::mouseDown(const juce::MouseEvent& event)
{
    
    //DBG("pressing the waveform" );
    if (fileLoaded)
    {
        soundElement.setPositionRelative((double)event.x/(double)getWidth());

    }
    
    
}
void  Waveform::mouseDrag(const juce::MouseEvent& event)
{
    
        //DBG("WaveFrom::mouseDrag x/ getWidth()  " << event.x / (double)getWidth());
    if (fileLoaded)
    {

        if (event.x < 0)
        {
            //DBG("WaveFrom::mouseDrag less than zero");
            soundElement.setPositionRelative(0);
        } 
        else if (event.x > getWidth())
        {
            //DBG("WaveFrom::mouseDrag greater than width");
            soundElement.setPositionRelative(1);
        }
        else
        {
            //DBG("WaveFrom::mouseDrag in the zone");
            soundElement.setPositionRelative(event.x / ( double )getWidth());
        }
    }
    

}

void Waveform::resetFileLoaded()
{
    fileLoaded = false;
}
