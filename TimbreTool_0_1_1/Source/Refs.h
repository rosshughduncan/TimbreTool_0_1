/*
  ==============================================================================

    Refs.h
    Created: 16 Aug 2020 6:15:34pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct VoidRef
{
    //std::unique_ptr<void> ref;
    void *ref;
};

struct WindowMethodRef
{
    juce::dsp::WindowingFunction<double>::WindowingMethod &ref;
};

