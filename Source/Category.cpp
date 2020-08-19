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
    clips = std::make_unique<std::vector<Clip*>>();
}

Category::~Category()
{
    // Delete all references to clip data in category
    for (Clip *currentClip : *clips) {
        delete currentClip;
    }
}

void Category::AddNewClip(std::string filePath, std::string fileName, juce::AudioFormatManager &audioFormatManRef, juce::dsp::WindowingFunction<double>::WindowingMethod &windowRef, double &framesFileRef)
{
    Clip *newClip = new Clip(filePath, fileName, audioFormatManRef, windowRef, framesFileRef);
    clips->push_back(newClip);
}
