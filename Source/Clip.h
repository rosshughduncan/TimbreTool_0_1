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
#include "Frames.h"

class Clip
{
public:
    Clip(std::string &filePath, std::string &fileName, juce::AudioFormatManager &audioFormatManRef, juce::dsp::WindowingFunction<float>::WindowingMethod &windowRef, double &framesFileRef);
    ~Clip();
    void ProcessWindows(double &framesFileRef);
private:
    // Properties of a clip:
    // File path, number of samples, number of channels, number of frames, sample rate, time, name, window function to be used
    std::string path, name;
    int numSamples, thisSampleRate, numSamplesSplit, numFrames, currentStartSample, currentSampleRange;
    juce::dsp::WindowingFunction<float>::WindowingMethod &windowMethodRef;
    juce::dsp::WindowingFunction<float> clipWindowFunction;
    splitTime times;
    
    // Audio data and frames
    juce::AudioBuffer<float>* audioBuffer;
    std::unique_ptr<std::vector<Frames*>> clipFrames;
    
    // Format reader
    juce::AudioFormatReader *formatReader;
};
