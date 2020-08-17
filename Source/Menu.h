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
    std::array<WindowMethodRef, 8> *windowFuncs;
    void transientDetectionSettings(), windowingSettings(), addNewAudioFile(), viewProperties(), exit();
    std::array<std::function<void()>, 5> *menuFuncs;
    std::shared_ptr<std::vector<std::shared_ptr<Category>>> &categoryRef;
    std::shared_ptr<std::vector<std::string>> &catListRef;
    juce::AudioFormatManager &formatManReference;

public:
    Menu(std::shared_ptr<std::vector<std::shared_ptr<Category>>> &categories, std::shared_ptr<std::vector<std::string>> &categoryListRef, juce::AudioFormatManager &formatManRef);
    ~Menu();
    void run();
};
