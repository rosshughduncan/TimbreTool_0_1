/*
  ==============================================================================

    Clip.cpp
    Created: 16 Aug 2020 6:16:19pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Clip.h"

Clip::Clip(std::string &filePath, std::string &fileName, juce::AudioFormatManager &audioFormatManRef, juce::dsp::WindowingFunction<float>::WindowingMethod &windowRef, double &framesFileRef) : path(filePath), name(fileName), numSamples(0), /*numChannels(0),*/ numFrames(0), windowMethodRef(windowRef), clipWindowFunction(64, windowMethodRef), audioBuffer(new juce::AudioBuffer<float>())
{
    std::cout << "Loading new clip...";
    
    // Create file reader and load data into buffer
    juce::File file(path);
    formatReader = (juce::AudioFormatReader*) malloc(120);
    formatReader = audioFormatManRef.createReaderFor(file);
    juce::String test = formatReader->getFormatName();
    numSamples = juce::roundToInt(formatReader->lengthInSamples);
    thisSampleRate = formatReader->sampleRate;
    audioBuffer->setSize(formatReader->numChannels, numSamples);
    formatReader->read(audioBuffer, 0, numSamples, 0, false, false);
    
    // Calculate times
    int rawLength = numSamples / thisSampleRate;
    double rawMins = rawLength / 60.0;
    times.hours = juce::roundToInt(floor(rawMins / 60.0));
    times.mins = juce::roundToInt(floor(fmod(rawMins, 60.0)));
    times.secs = juce::roundToInt(floor(fmod(rawLength, 60.0)));
    times.millisecs = juce::roundToInt(round(fmod(rawLength, 1.0) * 1000.0));
    
    // Apply the windowing processing
    ProcessWindows(framesFileRef);
}

Clip::~Clip()
{
    delete formatReader;
    delete audioBuffer;
    
    // Delete all frames in this clip
    for (Frames *currentFrame : *clipFrames) {
        delete currentFrame;
    }
}

void Clip::ProcessWindows(double &framesFileRef)
{
    /**
    * Split buffer into frames
    */
    
    // Calculate sample length per frame with given sample rate
    numSamplesSplit = ceil(framesFileRef * 0.001 * thisSampleRate);
    
    // Create frame objects
    numFrames = ceil(numSamples / numSamplesSplit);
    clipFrames = std::make_unique<std::vector<Frames*>>();
    
    // Set up windowing method
    
    
    // Read audio into each frame, ensuring the reading does not go outside the bounds of the audio buffer. Each frame executes the windowing function individually
    currentStartSample = 0;
    currentSampleRange = numSamplesSplit;
    for (int i = 1; i <= numFrames; i++) {
        if (currentStartSample + numSamplesSplit > numSamples) {
            currentSampleRange = numSamples - currentStartSample;
        }
        Frames *frame = new Frames(currentStartSample, currentSampleRange, audioBuffer, formatReader, clipWindowFunction);
        clipFrames->push_back(frame);
    }
    
    std::cout << "here";
}
