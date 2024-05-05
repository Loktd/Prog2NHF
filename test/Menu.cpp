#include "Menu.h"

#include <iostream>
#include <string>

void App::displayWelcomeScreen() const
{
    for (size_t i = 0; i < 2; i++)
        printSeparatorLine(std::cout, '=', 100);
    std::cout << "WELCOME TO CIRCUIT SIMULATOR!" << std::endl;
    for (size_t i = 0; i < 2; i++)
        printSeparatorLine(std::cout, '=', 100);
}

void App::displayMainMenu() const
{
    const size_t count = 6;
    printSeparatorLine(std::cout, '-', 100);
    std::string printed[count] = {
        "MAIN MENU", "1. Simulate", "2. Load circuit from file", "3. Set input combination", "4. Set output stream", "5. Quit"
    };
    for (size_t i = 0; i < count; i++) {
        std::cout << printed[i] << std::endl;
    }
}

void App::displayQuit() const
{
    for (size_t i = 0; i < 2; i++)
        printSeparatorLine(std::cout, '=', 100);
    std::cout << "QUITTING..." << std::endl;
    for (size_t i = 0; i < 2; i++)
        printSeparatorLine(std::cout, '=', 100);
}

void App::switchToSelectedMenu()
{
    const size_t menuCount = 5;
    std::cout << "Selected option: ";
    size_t inputted;
    if (std::cin >> inputted) {
        if (inputted == 0 || inputted > menuCount) {
            std::cout << std::endl << "INCORRECT INPUT!!!" << std::endl;
        }
        else {
            state = MenuState(1 + inputted);
        }
    }
    else {
        std::cout << std::endl << "INCORRECT INPUT!!!" << std::endl << std::endl;
        std::cin.clear();
        std::string clearer;
        std::cin >> clearer;
        std::cin.get();
    }
}

void App::loadCircuitFromName()
{
    std::string input;
    std::cin >> input;
    circuit.setSchematicsFile(input);
    state = MAIN_MENU;
}

void App::setOutStream()
{
    std::string input;
    std::cin >> input;
    if (input == "cout") {
        os = &std::cout;
    }
    else {
        ofs.open(input);
        if (ofs.is_open()) {
            os = &ofs;
        }
        else {
            std::cerr << "No input file with name: " << input << std::endl;
        }
    }
    state = MAIN_MENU;
}

void App::getSetComboType()
{
    size_t input;
    std::cin >> input;
    if (input == 0 || input > 2) {
        std::cout << std::endl << "INCORRECT INPUT!!!" << std::endl;
        state = MAIN_MENU;
    }
    else if (input == 1) {
        state = SETSOURCE;
    }
    else {
        state = SETSWITCH;
    }
}

void App::setSource()
{
    size_t input;
    bool newValue;

    std::cout << "Connected node: ";
    std::cin >> input;
    std::cout << "New value (0 = LOW, 1 = HIGH): ";
    std::cin >> newValue;

    circuit.setSource(input, Signal(newValue));

    state = MAIN_MENU;
}

void App::setSwitch()
{
    size_t input1, input2;
    bool newValue;

    std::cout << "Connected node no.1: ";
    std::cin >> input1;
    std::cout << "Connected node no.2: ";
    std::cin >> input2;
    std::cout << "New state (0 = open, 1 = closed): ";
    std::cin >> newValue;

    circuit.setSwitch(input1, input2, newValue);

    state = MAIN_MENU;
}

App::App() : run(true), state(START), os(&std::cout) {}

void App::stopRunning()
{
    run = false;
}

bool App::keepRunning() const
{
    return run;
}

void App::display() const
{
    switch (state)
    {
    case START:
        displayWelcomeScreen();
        break;
    case MAIN_MENU:
        displayMainMenu();
        break;
    case SIMULATE:
        std::cout << std::endl << "SIMULATING..." << std::endl << std::endl;
        break;
    case LOAD:
        std::cout << "Selected file: ";
        break;
    case SETCOMBO:
        std::cout << "Which do you wish to change?" << std::endl;
        std::cout << "1. Source" << std::endl << "2. Switch" << std::endl;
        std::cout << "Selected option: ";
        break;
    case SETOUTPUT:
        std::cout << "Selected output: ";
        break;
    case QUIT:
        displayQuit();
        break;

    default:
        break;
    }
}

void App::handleInput()
{
    switch (state)
    {
    case START:
        state = MAIN_MENU;
        break;
    case MAIN_MENU:
        switchToSelectedMenu();
        break;
    case SIMULATE:
        circuit.simulate(*os);
        std::cout << "SIMULATION DONE" << std::endl;
        state = MAIN_MENU;
        break;
    case LOAD:
        loadCircuitFromName();
        break;
    case SETCOMBO:
        getSetComboType();
        break;
    case SETSOURCE:
        setSource();
        break;
    case SETSWITCH:
        setSwitch();
        break;
    case SETOUTPUT:
        setOutStream();
        break;
    case QUIT:
        stopRunning();
        break;

    default:
        stopRunning();
        break;
    }
}

App::~App()
{
    if (ofs.is_open()) {
        ofs.close();
    }
}
