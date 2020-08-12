/*
  ==============================================================================

    Clip.cpp
    Created: 9 Aug 2020 6:43:26pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Clip.h"

Clip::Clip(std::string &filePath, std::string &fileName, juce::AudioFormatManager &audioFormatManRef, juce::dsp::WindowingFunction<double>::WindowingMethod &windowRef)
{
    std::cout << "Loading new clip...";
    
    // Initialise data members
    path = filePath;
    name = fileName;
    windowMethodRef = windowRef;
    
    // Create file reader and load data into buffer
    juce::File file(path);
    juce::AudioFormatReader* formatReader = audioFormatManRef.createReaderFor(file);
    numSamples = juce::roundToInt(formatReader->lengthInSamples);
    numChannels = formatReader->numChannels;
    audioBuffer->setSize(numChannels, numSamples);
    formatReader->read(audioBuffer, 0, numSamples, 0, false, false);
    
}

Clip::~Clip()
{
    delete audioBuffer;
}
