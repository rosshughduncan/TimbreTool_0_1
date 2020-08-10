/*
  ==============================================================================

    Menu.h
    Created: 10 Aug 2020 7:11:43pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Menu// : public juce::Thread
{
private:
    bool running;
    short menuOptionSelected, windowOptionSelected, validShortInput();
    int validIntInput(), framesFile, framesTransient, intGreaterThan0();
    double detectionFreq, highFreqWeight, validDoubleInput();
    std::string validPath();

public:
    Menu();
    ~Menu();// override;
    void run();// override;
};
