/*
  ==============================================================================

    Clip.h
    Created: 9 Aug 2020 6:43:26pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include <iostream>
#include <JuceHeader.h>

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
};
*
