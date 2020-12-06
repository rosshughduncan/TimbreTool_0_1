/*
  ==============================================================================

    Frames.h
    Created: 22 Nov 2020 3:45:15pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Frames
{
public:
    Frames(int startSample, int numSamples, juce::AudioBuffer<float> *&bufferToReadFrom, juce::AudioFormatReader *formatReaderRef, juce::dsp::WindowingFunction<float> &clipWindowFunctionRef);
    ~Frames();
    
private:
    std::complex<float> **frameAudioBuffers;
    std::complex<float> **frameFFTBuffers;
    juce::dsp::FFT frameFFT;
};
