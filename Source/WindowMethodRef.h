/*
  ==============================================================================

    WindowMethodRef.h
    Created: 12 Aug 2020 10:31:27pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct WindowMethodRef
{
    juce::dsp::WindowingFunction<double>::WindowingMethod &ref;
};
