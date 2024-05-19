#ifndef NODE_H_
#define NODE_H_

#include "InputComponent.h"
#include "OutputPin.h"
#include "../test/memtrace.h"

class Node : public InputComponent {
    /**
     * @brief A csomópont ID-ja, azaz a felhasználó által megadott száma, ez alapján lehet azonosítani egy csomópontot összekötéskor.
     *
     */
    size_t ID;

    /**
     * @brief A kimeneti pin-ek láncolt listája, nem tömb a gyors növelhetőség miatt, hiszen létrehozáskor nem tudjuk előre hogy hány lesz.
     *
     */
    Queue<OutputPin> outputPins;
public:
    /**
     * @brief Létrehozza a csomópontot 1 bemenettel, és 0 kimenettel, illetve beállítja az ID-t.
     *
     * @param nodeID A csomópont beállított ID-ja.
     */
    Node(size_t nodeID);

    /**
     * @brief Visszaadja a csomópont ID-ját, főleg azonosításhoz használjuk.
     *
     * @return size_t A csomópont ID-ja.
     */
    size_t getID() const;

    /**
     * @brief Visszaadja az egyetlen bemeneti pin-jét.
     *
     * @return InputPin* A bemeneti pin címe.
     */
    InputPin* getInPin();

    /**
     * @brief Hozzáad a kimeneti pin-ek láncolt listájához egy új pin-t, a kívánt végponttal.
     *
     * @param endPoint Ahova küldi majd a jelet a csomópont ezen a kimeneti pin-en.
     */
    void addOutputPin(InputPin* endPoint);

    /**
     * @brief Végrehajtja a funkcióját, azaz minden kimeneti pin-en kiküldi a bemeneti pin-en talált jelet.
     *
     */
    virtual void executeFunction();

    /**
     * @brief Virtuális destruktor az öröklés miatt.
     *
     */
    virtual ~Node();
};

#endif // NODE_H_