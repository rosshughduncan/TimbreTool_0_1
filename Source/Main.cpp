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
        
    //std::unique_ptr<std::vector<std::unique_ptr<Category>>> categories(new std::vector<std::unique_ptr<Category>>);
    //std::shared_ptr<std::vector<std::unique_ptr<Category>>> categories(new std::vector<std::unique_ptr<Category>>);
    std::shared_ptr<std::vector<std::shared_ptr<Category>>> categories(new std::vector<std::shared_ptr<Category>>);
    // List of audio clip categories
    //std::unique_ptr<std::vector<std::string>> categoryList(new std::vector<std::string>);
    std::shared_ptr<std::vector<std::string>> categoryList(new std::vector<std::string>);
    // Format manager
    juce::AudioFormatManager formatManager;
    
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
