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


class VinylCenter : juce::Component
{
public:
    VinylCenter() = default;
    ~VinylCenter() override;

    void setup();

    juce::Colour colour;
    Track* track;
    float& rotation;

    float centerPoint;
    float stepSize;
    float startPosXY;
    float startSizeXY;

    void paint(juce::Graphics&) override;
    void resized() override;
};



//==============================================================================
/*
*/
class Vinyl  :  public juce::Component,
                public juce::Timer
{
public:
    Vinyl() = default;
    ~Vinyl() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
    float calculateAngle(int x, int y);
    float previousAngle;
    int previousX;
    bool dragging;

    void timerCallback() override;

    void setupVinyl(Track*,juce::Colour, SoundElement*);
    void loadInTrack(Track* track);

    void paint (juce::Graphics&) override;
    void resized() override;

    void updateRotation();
    void drawUpdate();

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

    //juce::Graphics* graphics;
    //bool resizedBool;
    //VinylCenter vinylCenter;
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

