/*
  ==============================================================================

    Menu.cpp
    Created: 10 Aug 2020 7:11:43pm
    Author:  Ross Duncan

  ==============================================================================
*/

#include "Menu.h"

Menu::Menu(){}// : Thread::Thread("MainMenu") {}

Menu::~Menu()
{
    std::cout << "Thread killed by force";
    //this->stopThread(1000);
}

void Menu::run()
{
    // Private variables
    running = true;
    
    // Keep program running unless we select exit
    do {
        // Menu section
        std::cout << "Welcome to TimbreTool." << std::endl << std::endl;
        std::cout << "Enter a key based on one of the options:" << std::endl;
        std::cout << "1) Set transient detection settings" << std::endl;
        std::cout << "2) Set windowing settings" << std::endl;
        std::cout << "3 Add new audio file" << std::endl;
        std::cout << "4) View properties of an existing file" << std::endl;
        std::cout << "5) Exit";
        menuOptionSelected = validShortInput();
        
        // Key selection test
        switch (menuOptionSelected) {
            case 1:
                // Transient detection settings
                std::cout << std::endl << "Enter detection frequency crossover (Hz): ";
                detectionFreq = validDoubleInput();
                std::cout << std::endl << "Enter high frequency weighting (dB): ";
                highFreqWeight = validDoubleInput();
                break;
                
            case 2:
                // Windowing settings
                std::cout << std::endl << "Enter a number from the following list of windowing functions:"
                    << std::endl << "1) Rectangular"
                    << std::endl << "2) Triangular"
                    << std::endl << "3) Hann"
                    << std::endl << "4) Hamming"
                    << std::endl << "5) Blackman"
                    << std::endl << "6) Blackman-Harris"
                    << std::endl << "7) Flat Top"
                    << std::endl << "8) Kaiser";
                windowOptionSelected = validShortInput();
                std::cout << std::endl << "Enter the number of frames for the whole file:";
                framesFile = intGreaterThan0();
                std::cout << "Enter the number of frames for each transient:";
                framesTransient = intGreaterThan0();
                break;
                
            case 3:
                // Add new audio file
                std::cout << std::endl << "Enter the address of the file or drag it into this window:";
                
                break;
                
            case 4:
                // View properties of existing file
                
                break;
                
            case 5:
                // Exit
                running = false;
                break;
        }
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

int Menu::intGreaterThan0 ()
{
    int temp;
    
    while (true) {
        temp = validIntInput();
        if (temp < 1) {
            std::cout << std::endl << "Invalid number. It must be greater than 0. Please try again." << std::endl;
        }
        else {
            break;
        }
    }
    
    return temp;
}

std::string Menu::validPath()
{
    std::string temp;
    
    while (true) {
        std::cin >> temp;
        if (temp.length() == 0) {
            std::cout << std::endl << "You have not entered a file path. Please try again." << std::endl;
        }
        else {
            break;
        }
    }
    
    return temp;
}
