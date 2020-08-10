/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Menu.h"
#include <thread>

//==============================================================================
int main (int argc, char* argv[])
{
    // Run menu thread
    std::unique_ptr<Menu> mainMenu(new Menu());
    std::thread menuThread{mainMenu->run()};
    menuThread.join();
    //std::thread menuThread([&mainMenu]() { mainMenu->run(); });
    
    //Menu *mainMenu = new Menu();
    //mainMenu->startThread();
    //mainMenu->stopThread(1000);
    //delete mainMenu;

    
    return 0;
}
