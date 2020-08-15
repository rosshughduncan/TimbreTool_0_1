/*
  ==============================================================================

    FunctionRef.h
    Created: 13 Aug 2020 11:40:56pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once

//struct VoidRef
//{
//    std::unique_ptr<void> &ref;
//};

struct WindowMethodRef
{
    juce::dsp::WindowingFunction<double>::WindowingMethod &ref;
};
