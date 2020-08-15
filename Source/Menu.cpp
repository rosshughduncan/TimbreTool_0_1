/*
  ==============================================================================

    Menu.cpp
    Created: 10 Aug 2020 7:11:43pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Menu.h"

// : Thread::Thread("MainMenu") {}
Menu::Menu(std::unique_ptr<std::vector<Clip>> &clips, juce::AudioFormatManager &formatManRef) : clipsRef(clips), formatManReference(formatManRef)
{
    // Set default windowing function to Rectangular
    windowOption = 0;
    
    // Set references to windowing method enums
    windowFuncs = std::make_unique<WindowMethodRef[]>(8);
    windowFuncs[0].ref = juce::dsp::WindowingFunction<double>::WindowingMethod::rectangular;
    windowFuncs[1].ref = juce::dsp::WindowingFunction<double>::WindowingMethod::triangular;
    windowFuncs[2].ref = juce::dsp::WindowingFunction<double>::WindowingMethod::hann;
    windowFuncs[3].ref = juce::dsp::WindowingFunction<double>::WindowingMethod::hamming;
    windowFuncs[4].ref = juce::dsp::WindowingFunction<double>::WindowingMethod::blackman;
    windowFuncs[5].ref = juce::dsp::WindowingFunction<double>::WindowingMethod::blackmanHarris;
    windowFuncs[6].ref = juce::dsp::WindowingFunction<double>::WindowingMethod::flatTop;
    windowFuncs[7].ref = juce::dsp::WindowingFunction<double>::WindowingMethod::kaiser;
    
    // Set references to menu functions
    menuFunctions = std::make_unique<VoidRef[]>(5);
    menuFunctions[0].ref = Menu::transientDetectionSettings();
    menuFunctions[1].ref = Menu::windowingSettings();
    menuFunctions[2].ref = Menu::addNewAudioFile();
    menuFunctions[3].ref = Menu::viewProperties();
    menuFunctions[4].ref = Menu::exit();
}

Menu::~Menu()
{
    std::cout << "Menu killed";
    //this->stopThread(1000);
}

//void Menu::run(std::unique_ptr<std::vector<Clip>> &clips, juce::AudioFormatManager &formatManRef)
void Menu::run()
{
    // Private variables
    running = true;
    
    // Keep program running unless we select exit
    do {
        // Menu section
        std::cout << "Welcome to TimbreTool." << std::endl << std::endl;
        std::cout << "Enter a key based on one of the options and press enter:" << std::endl;
        std::cout << "1) Set transient detection settings" << std::endl;
        std::cout << "2) Set windowing settings" << std::endl;
        std::cout << "3 Add new audio file" << std::endl;
        std::cout << "4) View properties of an existing file" << std::endl;
        std::cout << "5) Exit";
        menuOptionSelected = validShortInput() - 1;
        
        // Execute the appropriate function according to the input number
//        auto currentFunc = menuFunctions[menuOptionSelected].ref.release();
//        ((void(*)())currentFunc)();
        ((void(*)())menuFunctions[menuOptionSelected].ref.release())();
    } while (running);
}

double Menu::validDoubleInput ()
{
    double temp;
    bool ok = false;
    
    while (!ok) {
        ok = true;
        try {
            std::cin >> temp;
        }
        catch(int e) {
            std::cout << "Invalid number. Error no: " << e << "Please try again (should be a floating point number)." << std::endl;
            ok = false;
        }
    }
    
    return temp;
}

short Menu::validShortInput ()
{
    short temp;
    bool ok = false;
    
    while (!ok) {
        ok = true;
        try {
            std::cin >> temp;
        }
        catch(int e) {
            std::cout << "Invalid number. Error no: " << e << " Please try again (should be a whole number)." << std::endl;
            ok = false;
        }
    }
    
    return temp;
}

int Menu::validIntInput ()
{
    int temp;
    bool ok = false;
    
    while (!ok) {
        ok = true;
        try {
            std::cin >> temp;
        }
        catch(int e) {
            std::cout << "Invalid number. Error no: " << e << " Please try again (should be a whole number)." << std::endl;
            ok = false;
        }
    }
    
    return temp;
}

double Menu::doubleGreaterThan0 ()
{
    double temp;
    
    while (true) {
        temp = validIntInput();
        if (temp <= 0.0) {
            std::cout << std::endl << "Invalid number. It must be greater than 0. Please try again." << std::endl;
        }
        else {
            break;
        }
    }
    
    return temp;
}

std::string Menu::validString(std::string stringType)
{
    std::string temp;
    
    while (true) {
        std::cin >> temp;
        if (temp.length() == 0) {
            std::cout << std::endl << "You have not entered a " << stringType << ". Please try again." << std::endl;
        }
        else {
            break;
        }
    }
    
    return temp;
}

std::unique_ptr<void> Menu::transientDetectionSettings()
{
    // Transient detection settings
    std::cout << std::endl << "Enter detection frequency crossover (Hz): ";
    detectionFreq = validDoubleInput();
    std::cout << std::endl << "Enter high frequency weighting (dB): ";
    highFreqWeight = validDoubleInput();
}

std::unique_ptr<void> Menu::windowingSettings()
{
    /**
     * Windowing settings
     */
    
    // Show windowing settings
    std::cout << std::endl << "Enter a number from the following list of windowing functions:"
        << std::endl << "1) Rectangular"
        << std::endl << "2) Triangular"
        << std::endl << "3) Hann"
        << std::endl << "4) Hamming"
        << std::endl << "5) Blackman"
        << std::endl << "6) Blackman-Harris"
        << std::endl << "7) Flat Top"
        << std::endl << "8) Kaiser";
    
    // Store the enum stored at the index chosen by the user, set to zero indexing
    windowOption = validShortInput() - 1;
    std::cout << std::endl << "Enter frame length (ms):";
    framesFile = doubleGreaterThan0();
}

std::unique_ptr<void> Menu::addNewAudioFile()
{
    // Add new audio file
    std::cout << std::endl << "Enter the address of the file or drag it into this window:";
    filePath = validString("file path");
    std::cout << std::endl << "Enter a name for this file:";
    fileName = validString("name");
    Clip newClip = new Clip(filePath, fileName, formatManReference, windowFuncs[windowOption].ref);
    clipsRef->push_back(newClip);
}

std::unique_ptr<void> Menu::viewProperties()
{
    // View properties of existing file
}

std::unique_ptr<void> Menu::exit()
{
    // Exit by setting flag to false
    running = false;
}
