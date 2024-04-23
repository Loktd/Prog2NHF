#include "../src/Circuit.h"

class App {
    enum MenuState {
        START = 0, MAIN_MENU = 1, SIMULATE = 2, LOAD = 3, SETCOMBO = 4, SETOUTPUT = 5, QUIT = 6,
        SETSOURCE = 7, SETSWITCH = 8,
    };

    Circuit circuit;
    bool run;
    MenuState state;

    std::ostream* os;
    std::ofstream ofs;

    void displayWelcomeScreen() const;
    void displayMainMenu() const;
    void displayQuit() const;

    void switchToSelectedMenu();
    void loadCircuitFromName();
    void setOutStream();
    void getSetComboType();
    void setSource();
    void setSwitch();
public:
    App();
    void stopRunning();
    bool keepRunning() const;
    void display() const;
    void handleInput();
    ~App();
};