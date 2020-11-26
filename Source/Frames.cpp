/*
  ==============================================================================

    Frames.cpp
    Created: 22 Nov 2020 3:45:15pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Frames.h"

Frames::Frames(int startSample, int numSamples, juce::AudioBuffer<float> *&bufferToReadFrom, juce::AudioFormatReader *formatReaderRef, juce::dsp::WindowingFunction<float> &clipWindowFunctionRef) :  frameAudioBuffers(new float*[formatReaderRef->numChannels]()), frameFFTBuffers(new float*[formatReaderRef->numChannels]()), frameFFT(9)
{
    // Set size of buffers
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        frameAudioBuffers[i] = new float[numSamples]();
        frameFFTBuffers[i] = new float[numSamples]();
    }
    
    // Load samples into buffers
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        for (int j = 0; j < numSamples; j++) {
            frameAudioBuffers[i][j] = bufferToReadFrom->getSample(i, j);
        }
    }
    
    // TESTING ONLY
    // Display contents of samples
    std::cout << "Pre-windowing: ";
    for (int i = 0; i < numSamples; i++) {
        std::cout << std::to_string(frameAudioBuffers[0][i])/* << "," << std::to_string(frameAudioBuffers[1][i])*/ << "\n";
    }
    std::cout << std::endl;
    
    // Apply windowing function and FFT
    for (int i = 0; i < formatReaderRef->numChannels; i++) {
        clipWindowFunctionRef.multiplyWithWindowingTable(frameAudioBuffers[i], 512);
        for (int j = 0; j < numSamples; j++) {
            frameFFTBuffers[i][j] = frameAudioBuffers[i][j];
        }
        
        // TESTING ONLY
//        std::cout << "\n\n\nTEST Pre-FFT ";
//        int fftSize = frameFFT.getSize();
//        int testSize = 2 * fftSize;
//        float *testBuffer = new float[testSize]();
//        for (int i = 0; i < fftSize; i++) {
//            testBuffer[i] = 0.00001 * i;
//            std::cout << testBuffer[i] << " ";
//        }
//        for (int i = fftSize; i < testSize; i++) {
//            testBuffer[i] = 0.0;
//            std::cout << testBuffer[i];
//        }
//        frameFFT.performFrequencyOnlyForwardTransform(testBuffer);
//        std::cout << "\nTEST Post-FFT";
//        for (; i < testSize; i++) {
//            std::cout << " " << testBuffer[i];
//        }
        
        //frameFFT.performFrequencyOnlyForwardTransform(frameFFTBuffers[i]);
    }
    
    // TESTING ONLY
    // Display contents of samples
    std::cout << "With window function applied: ";
    for (int i = 0; i < numSamples; i++) {
        std::cout << std::to_string(frameAudioBuffers[0][i])/* << "," << std::to_string(frameAudioBuffers[1][i])*/ << "\n";
    }
    std::cout << std::endl;
    
    // TESTING ONLY
    // Display contents of FFT
    std::cout << "FFT output: ";
    for (int i = 0; i < numSamples; i++) {
        std::cout << std::to_string(frameFFTBuffers[0][i])/* << "," << std::to_string(frameFFTBuffers[1][i])*/ << "\n";
    }
    std::cout << std::endl;
}

Frames::~Frames()
{
    // Delete buffers. As it is an array, we use the delete[] operator
    delete[] frameAudioBuffers;
    delete[] frameFFTBuffers;
}
