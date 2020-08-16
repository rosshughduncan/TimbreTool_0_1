/*
  ==============================================================================

    Category.h
    Created: 9 Aug 2020 6:43:18pm
    Author:  Ross Duncan

  ==============================================================================
*/

#pragma once
#include "Clip.h"

class Category
{
private:
    std::unique_ptr<std::vector<std::unique_ptr<Clip>>> clips;
    
public:
    Category();
    ~Category();
    void AddNewClip(std::string filePath, std::string fileName);
};
