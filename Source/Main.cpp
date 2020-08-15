#include <JuceHeader.h>
#include "Menu.h"
#include <thread>
#include "Clip.h"

int main (int argc, char* argv[])
{
    /**
    * Variables
    */
        
    // Storage of audio clips
    std::unique_ptr<std::vector<Clip>> clips(new std::vector<Clip>());
    // Format manager
    juce::AudioFormatManager formatManager;
    
    /**
    * Main threads
    */
    
    // Add server listener code here
    //******************************
    
    // Run menu thread
    Menu mainMenu(clips, formatManager);
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
