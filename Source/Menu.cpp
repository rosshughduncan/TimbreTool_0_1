/*
  ==============================================================================

    Menu.cpp
    Created: 16 Aug 2020 6:16:02pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Menu.h"

/**
 * By default:
 * > Windowing method is set to rectangular (0)
 * > Length of frames in each file is set to 10 ms
 */

Menu::Menu(std::shared_ptr<std::vector<std::shared_ptr<Category>>> &categories, std::shared_ptr<std::vector<std::string>> &categoryListRef, juce::AudioFormatManager &formatManRef) :
        windowOption(0),
        framesFile(10.0),
        windowFuncs(new std::array<WindowMethodRef, 8>()),
        menuFuncs(new std::array<std::function<void()>, 5>()), categoryRef(categories),
        catListRef(categoryListRef),
        formatManReference(formatManRef)
{
    // Set references to windowing method enums
    windowFuncs->at(0).ref = juce::dsp::WindowingFunction<double>::WindowingMethod::rectangular;
    windowFuncs->at(1).ref = juce::dsp::WindowingFunction<double>::WindowingMethod::triangular;
    windowFuncs->at(2).ref = juce::dsp::WindowingFunction<double>::WindowingMethod::hann;
    windowFuncs->at(3).ref = juce::dsp::WindowingFunction<double>::WindowingMethod::hamming;
    windowFuncs->at(4).ref = juce::dsp::WindowingFunction<double>::WindowingMethod::blackman;
    windowFuncs->at(5).ref = juce::dsp::WindowingFunction<double>::WindowingMethod::blackmanHarris;
    windowFuncs->at(6).ref = juce::dsp::WindowingFunction<double>::WindowingMethod::flatTop;
    windowFuncs->at(7).ref = juce::dsp::WindowingFunction<double>::WindowingMethod::kaiser;
    
    // Set references to menu functions
    menuFuncs->at(0) = [this]() { transientDetectionSettings(); };
    menuFuncs->at(1) = [this]() { windowingSettings(); };
    menuFuncs->at(2) = [this]() { addNewAudioFile(); };
    menuFuncs->at(3) = [this]() { viewProperties(); };
    menuFuncs->at(4) = [this]() { exit(); };
}

Menu::~Menu()
{
    delete menuFuncs;
    delete windowFuncs;
    std::cout << "Menu killed";
}

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
        menuFuncs->at(menuOptionSelected)();
        //((void(*)())menuFunctions[menuOptionSelected].ref.release())();
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
        //std::cin >> temp;
        std::cin.ignore();
        std::getline(std::cin, temp);
        if (temp.length() == 0) {
            std::cout << std::endl << "You have not entered a " << stringType << ". Please try again." << std::endl;
        }
        else {
            break;
        }
    }
    
    return temp;
}

void Menu::transientDetectionSettings()
{
    // Transient detection settings
    std::cout << std::endl << "Enter detection frequency crossover (Hz): ";
    detectionFreq = validDoubleInput();
    std::cout << std::endl << "Enter high frequency weighting (dB): ";
    highFreqWeight = validDoubleInput();
}

void Menu::windowingSettings()
{
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

void Menu::addNewAudioFile()
{
    // Store current path at front of file path
    filePath = fs::current_path();
    
    // Enter details for new audio file
    std::cout << std::endl << "Enter the name of the audio file stored in the AudioFiles folder (include any sub-directories and file extension, e.g. .wav):";
    //filePath = validString("file path");
    filePath = filePath + validString("file");
    std::cout << std::endl << "Enter a name for this file:";
    fileName = validString("name");
    std::cout << std::endl << "Enter a category (e.g. snare, bass, hi-hat, trumpet):";
    fileCategory = validString("category");
    
    // Find if category already exists. If not, add a new one
    auto begin = catListRef->begin();
    auto end = catListRef->end();
    auto findResult = std::find(begin, end, fileCategory);
    if (findResult != end) {
        foundIndex = (int)std::distance(begin, findResult);
        categoryRef->at(foundIndex)->AddNewClip(filePath, fileName, formatManReference, (windowFuncs->at(windowOption)).ref, framesFile);
    }
    else {
        catListRef->push_back(fileCategory);
        std::shared_ptr<Category> newCategory(new Category());
        newCategory->AddNewClip(filePath, fileName, formatManReference, (windowFuncs->at(windowOption)).ref, framesFile);
        categoryRef->push_back(newCategory);
    }
}

void Menu::viewProperties()
{
    // View properties of existing file
}

void Menu::exit()
{
    // Exit by setting flag to false
    running = false;
}
