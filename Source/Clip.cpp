/*
  ==============================================================================

    Clip.cpp
    Created: 16 Aug 2020 6:16:19pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Clip.h"

Clip::Clip(std::string &filePath, std::string &fileName, juce::AudioFormatManager &audioFormatManRef, juce::dsp::WindowingFunction<double>::WindowingMethod &windowRef) : path(filePath), name(fileName), windowMethodRef(windowRef)
{
    std::cout << "Loading new clip...";
    
    // Create file reader and load data into buffer
    juce::File file(path);
    juce::AudioFormatReader* formatReader = audioFormatManRef.createReaderFor(file);
    numSamples = juce::roundToInt(formatReader->lengthInSamples);
    numChannels = formatReader->numChannels;
    thisSampleRate = formatReader->sampleRate;
    audioBuffer->setSize(numChannels, numSamples);
    formatReader->read(audioBuffer, 0, numSamples, 0, false, false);
    
    // Calculate times
    int rawLength = numSamples / thisSampleRate;
    double rawMins = rawLength / 60.0;
    times.hours = juce::roundToInt(floor(rawMins / 60.0));
    times.mins = juce::roundToInt(floor(fmod(rawMins, 60.0)));
    times.secs = juce::roundToInt(floor(fmod(rawLength, 60.0)));
    times.millisecs = juce::roundToInt(round(fmod(rawLength, 1.0) * 1000.0));
    
    // Apply the windowing processing
    ProcessWindows();
}

Clip::~Clip()
{
    delete audioBuffer;
}

void Clip::ProcessWindows()
{
    // Split buffer into frames
}
