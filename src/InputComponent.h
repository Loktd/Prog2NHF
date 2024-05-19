#ifndef INPUTCOMPONENT_H_
#define INPUTCOMPONENT_H_

#include "InputPin.h"
#include "Component.h"
#include <iostream>
#include "../test/memtrace.h"


class InputPin;

class InputComponent : virtual public Component {
protected:
    /**
     * @brief A bemeneti pin-ek száma.
     *
     */
    size_t inputPinCount;

    /**
     * @brief A bemeneti pin-ek tömbje. Az index jelentését a specifikus alkatrész adja meg.
     *
     */
    InputPin* inputPins;

    /**
     * @brief A bemeneti csomópontok ID-jai kiolvasáshoz.
     *
     */
    size_t* inputNodeIDs;

public:
    /**
     * @brief Létrehozza a bemeneti pin-ek tömbjét.
     *
     * @param inputCount A bemeneti pin-ek száma.
     */
    InputComponent(size_t inputCount);

    /**
     * @brief Reseteli a bemeneti pin-ek státuszát szimulációhoz.
     *
     */
    void resetForSimulation();

    /**
     * @brief Ellenőrzi hogy minden bemeneti pin aktív-e, és berakja az aktív FIFO-ba, ha igen.
     *
     */
    void activateIfReady();

    /**
     * @brief Vissza adja a kívánt indexű bemeneti pin címét, ha létezik.
     *
     * @param idx A kívánt indexű pin.
     * @return InputPin* Az adott indexű pin.
     * @exception std::out_of_range = ha túlindexelünk.
     */
    InputPin* getInputPinByIndex(size_t idx) const;

    /**
     * @brief Beállítja egy bemeneti csompópont ID-t kiolvasáshoz.
     *
     * @param at A beállított bemenet indexe.
     * @param ID A beállított csomópont ID.
     * @exception std::out_of_range = ha túlindexelünk.
     */
    void setInputNodeID(size_t at, size_t ID);

    /**
     * @brief Ellenőri, hogy kapcsolódik-e egy adott csomóponthoz a bemenetén.
     *
     * @param ID A keresett csomópont ID-ja.
     * @return true = kapcsolódik hozzá a bemeneten ;
     * @return false = nem kapcsolódik hozzá a bemeneten
     */
    bool isConnectedToNodeOnInput(size_t ID);

    /**
     * @brief Kiírja a bemeneten csatlakoztatott csomópontok ID-ját.
     *
     * @param os A kimeneti stream, ahova akarjuk kiírni.
     */
    void printConnectedInputNodes(std::ostream& os) const;

    /**
     * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
     *
     */
    virtual void executeFunction() = 0;

    /**
     * @brief Törli a bemeneti pin-ek és ID-k tömbjét.
     *
     */
    virtual ~InputComponent();
};


#endif // INPUTCOMPONENT_H_