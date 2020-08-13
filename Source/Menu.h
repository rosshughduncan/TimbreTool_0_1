/*
  ==============================================================================

    Menu.h
    Created: 10 Aug 2020 7:11:43pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Clip.h"
#include "WindowMethodRef.h"
#include "VoidRef.h"

class Menu// : public juce::Thread
{
private:
    bool running;
    short menuOptionSelected, validShortInput(), windowOption;
    int validIntInput(), framesTransient;
    double detectionFreq, highFreqWeight, validDoubleInput(), framesFile, doubleGreaterThan0();
    std::string validString(std::string stringType), filePath, fileName;
    std::unique_ptr<WindowMethodRef[]> windowFuncs;
    //WindowMethodRef windowFuncs[8];
    //void *transientDetectionSettings(), *windowingSettings(), *addNewAudioFile(), *viewProperties(), *exit();
    std::unique_ptr<void> transientDetectionSettings, windowingSettings, addNewAudioFile, viewProperties, exit;
    std::unique_ptr<VoidRef[]> menuFunctions;

public:
    Menu();
    ~Menu();// override;
    void run(std::unique_ptr<std::vector<Clip>> &clips, juce::AudioFormatManager &formatManRef);// override;
};
