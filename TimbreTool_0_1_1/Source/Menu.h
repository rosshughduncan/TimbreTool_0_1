/*
  ==============================================================================

    Menu.h
    Created: 16 Aug 2020 6:16:02pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Refs.h"
#include "Category.h"
#include <array>
#include <algorithm>
#include <functional>

class Menu
{
private:
    bool running;
    short menuOptionSelected, validShortInput(), windowOption;
    int validIntInput(), framesTransient, foundIndex;
    double detectionFreq, highFreqWeight, validDoubleInput(), framesFile, doubleGreaterThan0();
    std::string validString(std::string stringType), filePath, fileName, fileCategory;
    std::unique_ptr<WindowMethodRef[]> windowFuncs;
    //std::unique_ptr<std::array<WindowMethodRef, 8>> windowFuncs;
    //std::array<WindowMethodRef, 8> *windowFuncs;
    //WindowMethodRef *windowFuncs;
    //std::unique_ptr<void> transientDetectionSettings(), windowingSettings(), addNewAudioFile(), viewProperties(), exit();
    void transientDetectionSettings(), windowingSettings(), addNewAudioFile(), viewProperties(), exit();
    //std::unique_ptr<VoidRef[]> menuFunctions;
    std::array<std::function<void>, 5> *menuFuncs;
    std::unique_ptr<std::vector<std::unique_ptr<Category>>> &categoryRef;
    std::unique_ptr<std::vector<std::string>> &catListRef;
    juce::AudioFormatManager &formatManReference;

public:
    Menu(std::unique_ptr<std::vector<std::unique_ptr<Category>>> &categories, std::unique_ptr<std::vector<std::string>> &categoryListRef, juce::AudioFormatManager &formatManRef);
    ~Menu();
    void run();
};
