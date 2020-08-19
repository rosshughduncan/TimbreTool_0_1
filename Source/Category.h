/*
  ==============================================================================

    Category.h
    Created: 16 Aug 2020 6:16:11pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include "Clip.h"
#include <JuceHeader.h>

class Category
{
private:
    std::unique_ptr<std::vector<Clip*>> clips;
    
public:
    Category();
    ~Category();
    void AddNewClip(std::string filePath, std::string fileName, juce::AudioFormatManager &audioFormatManRef, juce::dsp::WindowingFunction<double>::WindowingMethod &windowRef, double &framesFileRef);
};
