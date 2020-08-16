/*
  ==============================================================================

    Category.cpp
    Created: 9 Aug 2020 6:43:18pm
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

Category::AddNewClip(std::string filePath, std::string fileName)
{
    
}
