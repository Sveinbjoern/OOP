/*
  ==============================================================================

    Vinyl.h
    Created: 25 Mar 2022 6:32:45pm
    Author:  Angie Carola

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Vinyl  : public juce::Component
{
public:
    Vinyl();
    ~Vinyl() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vinyl)
};
