/*
  ==============================================================================

    Frames.cpp
    Created: 22 Nov 2020 3:45:15pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Frames.h"

Frames::Frames(int startSample, int numSamples, juce::AudioBuffer<float> *&bufferToReadFrom, juce::AudioFormatReader *formatReaderRef, juce::dsp::WindowingFunction<float> &clipWindowFunctionRef) :  frameAudioBuffers(new float*[formatReaderRef->numChannels])
{
    // Set size of buffers
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        frameAudioBuffers[i] = new float[numSamples]();
    }
    
    // Load samples into buffers
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        for (int j = 0; j < numSamples; j++) {
            frameAudioBuffers[i][j] = bufferToReadFrom->getSample(i, j);
        }
    }
    
    // TESTING ONLY
    // Display contents of samples
//    std::cout << "Pre-windowing: ";
//    for (int i = 0; i < numSamples; i++) {
//        std::cout << std::to_string(frameAudioBuffers[0][i]) << "," << std::to_string(frameAudioBuffers[1][i]) << "\n";
//    }
//    std::cout << std::endl;
    
    // Apply windowing function
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        clipWindowFunctionRef.multiplyWithWindowingTable(frameAudioBuffers[i], 64);
    }
    
    // TESTING ONLY
    // Display contents of samples
//    std::cout << "With window function applied: ";
//    for (int i = 0; i < numSamples; i++) {
//        std::cout << std::to_string(frameAudioBuffers[0][i]) << "," << std::to_string(frameAudioBuffers[1][i]) << "\n";
//    }
//    std::cout << std::endl;
}

Frames::~Frames()
{
    // Delete buffers. As it is an array, we use the delete[] operator
    delete[] frameAudioBuffers;
}
