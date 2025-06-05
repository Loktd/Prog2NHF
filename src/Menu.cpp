#include "Menu.h"

#include <iostream>
#include <string>

void App::stopRunning()
{
    run = false;
}

void App::clear_input() const
{
    std::cin.clear();
    std::string clearer;
    std::getline(std::cin, clearer);
}

void App::get_unsigned_with_check(size_t& input)
{
    if (!(std::cin >> input)) {
        clear_input();
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "INCORRECT INPUT..." << std::endl;
        switchToMainMenu();
        throw std::exception();
    }
    clear_input();
}

void App::displayWelcomeScreen() const
{

    printSeparatorLine(std::cout, '=', 100);
    std::cout << "WELCOME TO CIRCUIT SIMULATOR!" << std::endl;
    printSeparatorLine(std::cout, '=', 100);
}

void App::displayMainMenu() const
{
    printSeparatorLine(std::cout, '-', 100);

    const size_t count = 6;
    std::string printed[count] = {
        "MAIN MENU",
        "1. Simulate", "2. Load circuit from file", "3. Set input combination", "4. Set output stream", "5. Quit",
    };
    for (size_t i = 0; i < count; i++) {
        std::cout << printed[i] << std::endl;
    }
    printSeparatorLine(std::cout, '-', 100);
    std::cout << "Selected option: ";
}

void App::displaySimulating() const
{
    printSeparatorLine(std::cout, '-', 100);
    std::cout << "SIMULATING..." << std::endl << std::endl;
}

void App::displayLoading() const
{
    printSeparatorLine(std::cout, '-', 100);
    std::cout << "Selected file: ";
}

void App::displaySetCombination() const
{
    printSeparatorLine(std::cout, '-', 100);

    const size_t count = 3;
    std::string printed[count] = {
        "Which do you wish to change?",
        "1. Source", "2. Switch"
    };
    for (size_t i = 0; i < count; i++) {
        std::cout << printed[i] << std::endl;
    }
    printSeparatorLine(std::cout, '-', 100);
    std::cout << "Selected option: ";
}

void App::displaySetOutput() const
{
    printSeparatorLine(std::cout, '-', 100);
    std::cout << "Selected output: ";
}

void App::displayQuittingScreen() const
{
    printSeparatorLine(std::cout, '-', 100);
    printSeparatorLine(std::cout, '=', 100);
    std::cout << "QUITTING..." << std::endl;
    printSeparatorLine(std::cout, '=', 100);
}

void App::switchToMainMenu()
{
    state = MAIN_MENU;
}

void App::switchToSelectedMenu()
{
    const size_t menuCount = 5;
    size_t inputted;
    if (!(std::cin >> inputted) || inputted == 0 || inputted > menuCount) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "INCORRECT INPUT..." << std::endl;
        clear_input();
        return;
    }
    clear_input();
    state = MenuState(1 + inputted);
}

void App::executeSimulation()
{
    try {
        circuit.simulate(*simulation_os);
    }
    catch (ConfigurationError& error) {
        std::cout << "CONFIGURATION FAILED" << std::endl;
        std::cout << std::endl << "SIMULATION FAILED" << std::endl;
        switchToMainMenu();
        return;
    }
    std::cout << "SIMULATION SUCCESSFUL" << std::endl;
    switchToMainMenu();
}

void App::loadCircuitFromName()
{
    std::string input;
    std::getline(std::cin, input);
    circuit.setSchematicFile(input);
    switchToMainMenu();
}

void App::setSimulationOutputStream()
{
    std::string input;
    std::getline(std::cin, input);

    if (input == "terminal") {
        if (output_file.is_open())
            output_file.close();
        simulation_os = &std::cout;
        switchToMainMenu();
        return;
    }

    if (output_file.is_open())
        output_file.close();
    output_file.open(input, std::ios::app);

    if (output_file.is_open()) {
        simulation_os = &output_file;
    }
    else {
        std::cerr << "No input file with name: " << input << std::endl;
    }
    switchToMainMenu();
}

void App::getSetCombinationOption()
{
    size_t input;
    try { get_unsigned_with_check(input); }
    catch (...) { return; }

    if (input == 0 || input > 2) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "INCORRECT INPUT..." << std::endl;
        switchToMainMenu();
        return;
    }

    if (input == 1)
        state = SETSOURCE;
    else
        state = SETSWITCH;
}

void App::setSource()
{
    size_t input1;
    size_t input2;

    printSeparatorLine(std::cout, '-', 100);
    std::cout << "Connected node: ";
    try { get_unsigned_with_check(input1); }
    catch (...) { return; }

    printSeparatorLine(std::cout, '-', 100);
    std::cout << "New value (0 = LOW, 1 = HIGH): ";
    try { get_unsigned_with_check(input2); }
    catch (...) { return; }

    if (input2 >= 2) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "INCORRECT INPUT..." << std::endl;
        switchToMainMenu();
        return;
    }

    Signal set_value = Signal(static_cast<bool>(input2));

    try {
        printSeparatorLine(std::cout, '-', 100);
        circuit.setSource(input1, set_value);
    }
    catch (ConfigurationError& error) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "SET SOURCE FAILED, CIRCUIT COULDN'T BE CONFIGURED..." << std::endl;
    }
    catch (MatchingComponentNotFound& error) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "ERROR: ";
        std::cout << error.exception_message() << std::endl;
    }

    switchToMainMenu();
}

void App::setSwitch()
{
    size_t input[3];
    std::string messages[3]{
        "Connected node no.1: ", "Connected node no.2: ", "New state (0 = open, 1 = closed): "
    };

    for (size_t i = 0; i < 3; i++) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << messages[i];
        try { get_unsigned_with_check(input[i]); }
        catch (...) { return; }
    }

    if (input[2] >= 2) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "INCORRECT INPUT..." << std::endl;
        switchToMainMenu();
        return;
    }

    bool set_value = static_cast<bool>(input[3]);

    try {
        printSeparatorLine(std::cout, '-', 100);
        circuit.setSwitch(input[0], input[1], set_value);
    }
    catch (ConfigurationError& error) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "SET SWITCH FAILED, CIRCUIT COULDN'T BE CONFIGURED..." << std::endl;
    }
    catch (MatchingComponentNotFound& error) {
        printSeparatorLine(std::cout, '-', 100);
        std::cout << "ERROR: ";
        std::cout << error.exception_message() << std::endl;
    }

    switchToMainMenu();
}


// Publikus tagfüggvények

App::App() : state(START), run(true), simulation_os(&std::cout) {}

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
        displaySimulating();
        break;
    case LOAD:
        displayLoading();
        break;
    case SETCOMBO:
        displaySetCombination();
        break;
    case SETOUTPUT:
        displaySetOutput();
        break;
    case QUIT:
        displayQuittingScreen();
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
        switchToMainMenu();
        break;

    case MAIN_MENU:
        switchToSelectedMenu();
        break;
    case SIMULATE:
        executeSimulation();
        break;
    case LOAD:
        loadCircuitFromName();
        break;
    case SETCOMBO:
        getSetCombinationOption();
        break;
    case SETOUTPUT:
        setSimulationOutputStream();
        break;
    case QUIT:
        stopRunning();
        break;

    case SETSOURCE:
        setSource();
        break;
    case SETSWITCH:
        setSwitch();
        break;
    default:
        stopRunning();
        break;
    }
}

App::~App()
{
    if (output_file.is_open()) {
        output_file.close();
    }
}
