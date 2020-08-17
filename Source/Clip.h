/*
  ==============================================================================

    Clip.h
    Created: 16 Aug 2020 6:16:19pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include <iostream>
#include <JuceHeader.h>
#include "SplitTime.h"
#include <cmath>

class Clip
{
public:
    Clip(std::string &filePath, std::string &fileName, juce::AudioFormatManager &audioFormatManRef, juce::dsp::WindowingFunction<double>::WindowingMethod &windowRef);
    ~Clip();
private:
    // Properties of a clip:
    // File path, number of samples, number of channels, sample rate, time, name, audio data, window function
    std::string path, name;
    int numSamples, numChannels, thisSampleRate;
    juce::AudioBuffer<float>* audioBuffer;
    juce::dsp::WindowingFunction<double>::WindowingMethod &windowMethodRef;
    splitTime times;
};
