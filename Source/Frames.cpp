/*
  ==============================================================================

    Frames.cpp
    Created: 22 Nov 2020 3:45:15pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Frames.h"

Frames::Frames(int startSample, int numSamples, juce::AudioBuffer<float> *&bufferToReadFrom, juce::AudioFormatReader *formatReaderRef, juce::dsp::WindowingFunction<float> &clipWindowFunctionRef) :
    frameAudioBuffers(new std::complex<float>*[formatReaderRef->numChannels]()), frameFFTBuffers(new std::complex<float>*[formatReaderRef->numChannels]()), frameFFT(9)
{
    // Set size of buffers
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        frameAudioBuffers[i] = new std::complex<float>[numSamples]();
        
        // Output array is the FFT size
        frameFFTBuffers[i] = new std::complex<float>[frameFFT.getSize()];
    }
    
    // Load samples into frameAudioBuffers
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        for (int j = 0; j < numSamples; j++) {
            frameAudioBuffers[i][j] = bufferToReadFrom->getSample(i, j);
        }
    }
    
    // Apply windowing function and FFT (out of place
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        clipWindowFunctionRef.multiplyWithWindowingTable((float*)frameAudioBuffers[i], 512);
        frameFFT.perform(frameAudioBuffers[i], frameFFTBuffers[i], false);
    }
    
    // TESTING ONLY
    // Display contents of FFT
    std::cout << "FFT output: ";
    int testNumChannels = formatReaderRef->numChannels;
    //for (int i = 0; i < formatReaderRef->numChannels; i++) {
    //for (int i = 0; i < formatReaderRef->numChannels; ++i) {
    
    // i not incrementing!!!
    for (int i = 0; i < testNumChannels; i++) {
        std::cout << "Channel " << i << "\n";
        for (int j = 0; j < frameFFT.getSize(); j++) {
            std::cout << frameFFTBuffers[i][j].real() << "\n";
        }
    }
    std::cout << std::endl;
}

Frames::~Frames()
{
    // Delete buffers. As it is an array, we use the delete[] operator
    delete[] frameAudioBuffers;
    delete[] frameFFTBuffers;
}
