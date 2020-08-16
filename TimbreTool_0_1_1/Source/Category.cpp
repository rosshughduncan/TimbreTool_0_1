/*
  ==============================================================================

    Category.cpp
    Created: 16 Aug 2020 6:16:11pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Category.h"

Category::Category()
{
    clips = std::make_unique<std::vector<std::unique_ptr<Clip>>>();
}

Category::~Category()
{
}

void Category::AddNewClip(std::string filePath, std::string fileName, juce::AudioFormatManager &audioFormatManRef, juce::dsp::WindowingFunction<double>::WindowingMethod &windowRef)
{
    std::unique_ptr<Clip> newClip(new Clip(filePath, fileName, audioFormatManRef, windowRef));
    clips->push_back(newClip);
}
