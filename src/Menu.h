#include "Circuit.h"

class App {
    /**
     * @brief A menü lehetséges állapotai.
     *
     */
    enum MenuState {
        START = 0, MAIN_MENU = 1, SIMULATE = 2, LOAD = 3, SETCOMBO = 4, SETOUTPUT = 5, QUIT = 6,
        SETSOURCE = 7, SETSWITCH = 8,
    };

    /**
     * @brief Az áramkört tároló elem.
     *
     */
    Circuit circuit;
    /**
     * @brief A program állapota, azaz hogy melyik menüpontban van.
     *
     */
    MenuState state;
    /**
     * @brief Azt tárolja, hogy folytassa-e a futást a program.
     *
     */
    bool run;

    /**
     * @brief A szimuláció eredményéhez a kimeneti file.
     *
     */
    std::ofstream output_file;
    /**
     * @brief A kimeneti stream, ahova kiírja az eredményt. (azért kell, mert cout nem ofstream)
     *
     */
    std::ostream* simulation_os;

    /**
     * @brief Kitisztítja a std::cin-t, ha maradt benne garbage adat, miután helyetelen bemenetet adtunk meg.
     *
     */
    void clear_input() const;
    /**
     * @brief Beolvas egy unsigned int-et, és ellenőrzi ezt a beolvasást.
     * @brief Ha helytelen, akkor kitisztítja std::cin-t, jelzi a helytelen bemenetet és visszalép a főmenübe.
     *
     * @param input Ahova olvasunk.
     */
    void get_unsigned_with_check(size_t& input);

    /**
     * @brief Kiírja a köszöntő szöveget.
     *
     */
    void displayWelcomeScreen() const;
    /**
     * @brief Kiírja a főmenüt.
     *
     */
    void displayMainMenu() const;
    /**
     * @brief Kiírja a szimulálás előtti szöveget.
     *
     */
    void displaySimulating() const;
    /**
     * @brief Kiírja a file betöltés előtti szöveget.
     *
     */
    void displayLoading() const;
    /**
     * @brief Kiírja a bemeneti kombináció állítása előtti szöveget.
     *
     */
    void displaySetCombination() const;
    /**
     * @brief Kiírja a kimeneti file állítása előtti szöveget.
     *
     */
    void displaySetOutput() const;
    /**
     * @brief Kiírja a búcsúzó szöveget.
     *
     */
    void displayQuittingScreen() const;

    /**
     * @brief Főmenübe vált.
     *
     */
    void switchToMainMenu();
    /**
     * @brief Átvált a kiválasztott menüpontba.
     *
     */
    void switchToSelectedMenu();
    /**
     * @brief Végrehatja a szimulálás kezelését.
     *
     */
    void executeSimulation();
    /**
     * @brief Végrehatja az áramkör konfig file-jának beállítását.
     *
     */
    void loadCircuitFromName();
    /**
     * @brief Beolvassa hogy melyik almenüpontot választottuk.
     *
     */
    void getSetCombinationOption();
    /**
     * @brief Végrehatja a forrás állításának kezelését.
     *
     */
    void setSource();
    /**
     * @brief Végrehatja a kapcsoló állításának kezelését.
     *
     */
    void setSwitch();
    /**
     * @brief Végrehatja az áramkör kimeneti stream-jének beállítását.
     *
     */
    void setSimulationOutputStream();

    /**
     * @brief Leállítja a programot.
     *
     */
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