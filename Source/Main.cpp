/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Menu.h"
#include <thread>
//#include "Clip.h"
#include "Category.h"

int main (int argc, char* argv[])
{
    /**
    * Variables
    */
        
    // Audio clip categories
    std::shared_ptr<std::vector<std::shared_ptr<Category>>> categories(new std::vector<std::shared_ptr<Category>>);
    
    // List of audio clip category names
    std::shared_ptr<std::vector<std::string>> categoryList(new std::vector<std::string>);
    
    // Format manager
    juce::AudioFormatManager formatManager;
    
    // Register WAV and AIFF files
    formatManager.registerBasicFormats();
    
    /**
    * Main threads
    */
    
    // Add server listener code here
    //******************************
    
    // Run menu thread
    Menu mainMenu(categories, categoryList, formatManager);
    std::thread menuThread([&mainMenu] { mainMenu.run(); });
    menuThread.join();
    
    return 0;
}
