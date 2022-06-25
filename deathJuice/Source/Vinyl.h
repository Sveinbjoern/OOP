/*
  ==============================================================================

    Vinyl.h
    Created: 25 Mar 2022 6:32:45pm
    Author:  Angie Carola

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundElement.h"
#include "Track.h"
#include "SoundElement.h"


//==============================================================================
/*
*/
class Vinyl  :  public juce::Component,
                public juce::Timer
{
public:
    Vinyl() = default;
    ~Vinyl() override;

    //juce functions
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    


    /**sets up the vinyl after its creation*/
    void setupVinyl(Track*,juce::Colour, SoundElement*);
    /**loads a track into vinyl 
    takes a Track pointer as input */
    void loadInTrack(Track* track);

    /**updates the genereal rotation
    is in relation to the actual position of
    the player*/
    void updateRotation();

private:
    float centerPoint;
    float stepSize;
    float startPosXY;
    float startSizeXY;
    float posXY;
    float sizeXY;
    float stepSize100;
    float twentySteps;
    float letterxPos;
    float letteryPos;

    float previousAngle;
    int previousX;
    bool dragging;
    std::string s;

    std::vector<std::array<float, 4>> ringsVec;
    float drawLength[4];
    //float drawText[4];

    float innerPin[2];
    float outerPin[2];
    juce::Colour metallic;
    juce::Colour darkmetallic;

    int rings;
    float stride;
    float blackStride;
    float PI;

    Track* track;
    float calculateAngle(int x, int y);

    juce::String trackName;
    juce::String lengthString;
    int length;
    int half;
    float start;
    float textStep;
    int maxTextLength;

    float previousSoundPos;
    SoundElement* soundElement;
    float rotation;
    int steps;
    juce::Colour colour;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vinyl)
};

