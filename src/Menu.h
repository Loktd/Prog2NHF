#include "Circuit.h"

class App {
    enum MenuState {
        START = 0, MAIN_MENU = 1, SIMULATE = 2, LOAD = 3, SETCOMBO = 4, SETOUTPUT = 5, QUIT = 6,
        SETSOURCE = 7, SETSWITCH = 8,
    };

    Circuit circuit;
    MenuState state;
    bool run;

    std::ofstream output_file;
    std::ostream* simulation_os;

    void clear_input() const;
    void get_unsigned_with_check(size_t& input);

    void displayWelcomeScreen() const;
    void displayMainMenu() const;
    void displaySimulating() const;
    void displayLoading() const;
    void displaySetCombination() const;
    void displaySetOutput() const;
    void displayQuittingScreen() const;

    void switchToMainMenu();
    void switchToSelectedMenu();
    void executeSimulation();
    void loadCircuitFromName();
    void getSetCombinationOption();
    void setSource();
    void setSwitch();
    void setSimulationOutputStream();
    void stopRunning();
public:
    /**
     * @brief Létrehozza a programot, alapállapotba állítva.
     *
     */
    App();

    /**
     * @brief Visszaadja, hogy fusson-e még a program.
     *
     * @return true = még nem áll le az program ,
     * @return false = álljon le a program
     */
    bool keepRunning() const;

    /**
     * @brief Kijelzi az állapottól függően a menüt.
     *
     */
    void display() const;

    /**
     * @brief Kezeli a felhasználó bemenetét állapottól függően.
     *
     */
    void handleInput();

    /**
     * @brief Megszünteti a program memóriáját, bezárja a file-okat.
     *
     */
    ~App();
};