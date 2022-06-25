/*
  ==============================================================================

    Vinyl.cpp
    Created: 25 Mar 2022 6:32:45pm
    Author:  Angie Carola

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Vinyl.h"

//==============================================================================


Vinyl::~Vinyl()
{
    stopTimer();

}



void Vinyl::setupVinyl(Track* _track, juce::Colour _colour, SoundElement* se)
{
    soundElement = se;
    previousSoundPos = se->getPosition();

    PI = std::atan(1.0) * 4;

    textStep = 0.17;
    maxTextLength = 35;
    dragging = false;
    track = _track;
    colour = _colour;
    steps = 300;
    rotation = 0;

    centerPoint = 0;
    stepSize = 0;

    twentySteps = 0;
    rings = 0;
    
    startPosXY = posXY = 4;
    startSizeXY = sizeXY = getWidth() - startPosXY * 2;
    stride = 0;
    blackStride = 0;

    ringsVec.resize(rings);
    for (int i = 0; i < rings; ++i)
    {
        ringsVec[i][0] = posXY + 3;
        ringsVec[i][1] = posXY;
        ringsVec[i][2] = sizeXY - 3;
        ringsVec[i][3] = sizeXY;
        posXY += stride;
        sizeXY -= stride * 2;
    }


    letterxPos = 0;
    letteryPos = 0;

    metallic = juce::Colour(201, 192, 187);
    darkmetallic = juce::Colour(150, 149, 153);

   



    //resizedBool = true;

    //colour = juce::Colour(255, 0, 0);

    if (track == nullptr)
    {
        track = &Track();
        DBG("Vinyl::Vinyl track fullpath " << track->fullPath);
        track->setNoName();
        track->setTrackLengthString("0.0");
    }

    trackName = track->getFileName();
    lengthString = track->getTrackLengthString();
    
    lengthString.append(" s", 2);
    length = trackName.length();
    if (length > maxTextLength)
        length = maxTextLength;
    half = length / 2;
    start = -half*textStep;
        if (length % 2 == 0)
        {
            start -= (textStep / 2);
            
        }
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    DBG("Vinyl::Vinyl track filename " << track->getFileName());
    DBG("Vinyl::Vinyl track length " << track->getTrackLengthString());

    startTimer(60);
}


void Vinyl::paint (juce::Graphics& g)
{
    

    //DBG("Vinyl::paint rotation PI" << rotation << " " <<  PI);
       
    
    //rotation = std::atan(0)*2;
        //resizedBool = false;
        
    

    g.addTransform(juce::AffineTransform::rotation(rotation, centerPoint, centerPoint));
    //g.setColour();
    //g.setFillType(juce::FillType(juce::Colour(juce::Colours::black)));
    
    for (int i = 0; i < rings; ++i)
    {
        g.drawEllipse(ringsVec[i][0], ringsVec[i][1], ringsVec[i][2], ringsVec[i][3], blackStride);
    }
    //g.drawEllipse(startPosXY-0.5, startPosXY, startSizeXY+0.5, startSizeXY, blackStride);

    g.setFillType(juce::FillType(colour));
    
    g.fillEllipse(stepSize100, stepSize100, stepSize100, stepSize100);

    g.setColour (juce::Colours::white);
    g.setFont (11.0f);


    g.drawText (lengthString, drawLength[0], drawLength[1], drawLength[2], drawLength[3],
                juce::Justification::centred, true);   
    //DBG("start " << start);
    //float rot = rotation +start;
    //float tenSteps = stepSize * 10;


    

    g.addTransform(juce::AffineTransform::rotation(start, centerPoint, centerPoint));
    for (int i = 0; i < length; ++i)
    {
        s = trackName[i];
        g.drawText( s, letterxPos,letteryPos ,twentySteps , twentySteps, //getLocalBounds(),
            juce::Justification::centred, false);
        g.addTransform(juce::AffineTransform::rotation(textStep, centerPoint, centerPoint));
        //DBG("Vinyl::paint "<< trackName[i]);
    }
    //DBG("trackName[0] " << trackName[0]);
    //g.setFillType(juce::FillType(juce::Colour(0xaaa9ad)));
    
    
    g.setColour(darkmetallic);
    //g.setFillType(juce::FillType(darkmetallic));
    g.drawEllipse(outerPin[0], outerPin[0], outerPin[1], outerPin[1], 1.0f);
    //g.setFillType(juce::FillType(metallic));
    g.setColour(metallic);
    g.fillEllipse(innerPin[0], innerPin[0], innerPin[1], innerPin[1]);
}


void Vinyl::timerCallback()
{
    updateRotation();
    
    //DBG("Vinyl::timerCAllback repaint");
    repaint();


}

void Vinyl::loadInTrack(Track* _track)
{   
    if (_track == nullptr)
    {
        track = &Track();
        DBG("Vinyl::Vinyl track fullpath " << track->fullPath);
        track->setNoName();
        track->setTrackLengthString("0.0");
    }
    else
    {
        track = _track;
    }

    
    trackName = track->getFileName();
    lengthString = track->getTrackLengthString();
    lengthString.append(" s",2);
    length = trackName.length();
    if (length > maxTextLength)
        length = maxTextLength;
    half = length / 2;
    start = (-half) * textStep;
    if (length % 2 == 0)
    {
        start -= textStep / 2;
    }

}

void Vinyl::updateRotation()
{
    double temp = soundElement->getPosition();
    rotation += (temp - previousSoundPos)*0.55;
    previousSoundPos = temp;
}

void Vinyl::resized()
{
    //resizedBool = true;
    // This method is where you should set the bounds of any child
    // components that your component contains..

    centerPoint = (float)getWidth() / 2;
    stepSize = (float)getWidth() / steps;

    twentySteps = stepSize * 20;
    stepSize100 = stepSize * 100;
    //DBG("Vinyl::paint stepSize " << stepSize);
    rings = stepSize * 15;
    //DBG("Vinyl::paint rings " << rings);
    startPosXY = posXY = 4;
    startSizeXY = sizeXY = getWidth() - startPosXY * 2;
    stride = stepSize * 100 / rings;
    blackStride = stride * 0.95;
    
    ringsVec.resize(rings);
    for (int i = 0; i < rings; ++i)
    {
        ringsVec[i][0] = posXY + 3;
        ringsVec[i][1] = posXY;
        ringsVec[i][2] = sizeXY - 3;
        ringsVec[i][3] = sizeXY;
        posXY += stride;
        sizeXY -= stride * 2;
    }

    outerPin[0] = centerPoint - stepSize * 5;
    outerPin[1] = stepSize * 10;
    innerPin[0] = centerPoint - stepSize * 5 + 0.5;
    innerPin[1] = stepSize * 10 - 1;

    drawLength[0] = centerPoint - stepSize * 70;
    drawLength[1] = centerPoint + stepSize * 10;
    drawLength[2] = stepSize * 140;
    drawLength[3] = stepSize * 20;
   
    letterxPos = centerPoint - stepSize * 10;
    letteryPos = centerPoint - stepSize * 50;


}



//Events

void Vinyl::mouseDown(const juce::MouseEvent& event)
{
    previousX = event.x - centerPoint;
    previousAngle = calculateAngle(event.x-centerPoint, event.y-centerPoint);
    DBG("MouseDown " << event.x -centerPoint << " " << event.y - centerPoint << " angle " << previousAngle);
    dragging = true;


}

void Vinyl::mouseDrag(const juce::MouseEvent& event)
{
    
    float newAngle = calculateAngle(event.x-centerPoint, event.y-centerPoint);
    //DBG("MouseDrag " << " angle " << newAngle);
    double thingy = (newAngle - previousAngle)/0.55;
    soundElement->setPosition(thingy+soundElement->getPosition());
    previousAngle = newAngle;
}
void Vinyl::mouseUp(const juce::MouseEvent& event)
{
    dragging = false;
}

float Vinyl::calculateAngle(int x, int y)
{
    //if (x == 0)
    //    ++x;
    //DBG("Vinyl::calculateAngle previousX x " << previousX << " " << x);
    if (previousX <= 0)
    {
        
        if (x > 0)
        {
            DBG("Vinyl::calculateAngle previousX<=0 x>0  ");
            if (y < 0)
            {
                //DBG("Vinyl::calculateAngle x going positive top");
                previousAngle = -PI + previousAngle; // approved
            }
            else
            {
                DBG("Vinyl::calculateAngle x going positive bottom");
                previousAngle =  PI +previousAngle;
            }
        }     
    } 
    else
    {
        if (x <= 0)
        {
            //DBG("Vinyl::calculateAngle previousX >0 x<=0  ");
            if (y < 0)
            {
                //DBG("Vinyl::calculateAngle x going negative top");
                previousAngle = PI + previousAngle;//approved
            }
            else
            {
                DBG("Vinyl::calculateAngle x going negative bottom");
                previousAngle = -PI + previousAngle;
            }
               

        }
    }
    previousX = x;
    return std::atan((float)y/x );
}
