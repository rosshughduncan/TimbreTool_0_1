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
        
    // Storage of audio clips
    //std::unique_ptr<std::vector<std::unique_ptr<Clip>>> clips(new std::vector<std::unique_ptr<Clip>>());
    // Storage of audio clip categories
    std::unique_ptr<std::vector<std::unique_ptr<Category>>> categories(new std::vector<std::unique_ptr<Category>>);
    // List of audio clip categories
    std::unique_ptr<std::vector<std::string>> categoryList(new std::vector<std::string>);
    // Format manager
    juce::AudioFormatManager formatManager;
    
    /**
    * Main threads
    */
    
    // Add server listener code here
    //******************************
    
    // Run menu thread
    //Menu mainMenu(clips, formatManager);
    Menu mainMenu(categories, categoryList, formatManager);
    //std::thread menuThread([&mainMenu, &clips, &formatManager] { mainMenu.run(clips, formatManager); });
    std::thread menuThread([&mainMenu] { mainMenu.run(); });
    menuThread.join();
    
    return 0;
}

/**
 * Old code
 */

//std::thread menuThread(&Menu::run, &mainMenu);
//std::thread menuThread(mainMenu.run, clips);
//std::thread menuThread(mainMenu.run(clips));
