#ifndef OUTPUTCOMPONENT_H_
#define OUTPUTCOMPONENT_H_

#include "OutputPin.h"
#include "Component.h"
#include "InputComponent.h"
#include "memtrace.h"

class OutputComponent : virtual public Component {
protected:
    /**
     * @brief A kimeneti pin-ek száma.
     *
     */
    size_t outputPinCount;

    /**
     * @brief A kimeneti pin-ek tömbje. Az index jelentést a specifikus alkatrész adja meg.
     *
     */
    OutputPin* outputPins;

    /**
     * @brief A kimenet csomópontok ID-jai kiolvasáshoz.
     *
     */
    size_t* outputPinIDs;

public:
    /**
     * @brief Létrehozza a kimeneti pin-ek és csomópont ID-k tömbjét.
     *
     * @param outputCount A kívánt kimeneti pin-ek száma.
     */
    OutputComponent(size_t outputCount);

    /**
     * @brief Összeköti a megadott kimeneti pin-jét egy másik áramköri elem bemeneti pin-jével.
     *
     * @param outputPinIndex A kimeneti pin indexe.
     * @param component Amivel össze szeretnénk kötni.
     * @param inputPinIndex A bemeneti pin indexe.
     *
     * @exception Ha a kimeneti vagy bemeneti pin-ek tömbjén kívül indexelünk, akkor dob egy std::out_of_range-t.
     */
    void connectToInputPin(size_t outputPinIndex, InputComponent* component, size_t inputPinIndex);

    /**
     * @brief Kiküldi minden kimeneti lábán a lábakban tárolt jeleket.
     *
     */
    void sendOutSignals();

    /**
     * @brief Vissza adja a kívánt indexű kimeneti pin címét, ha létezik.
     *
     * @param idx A kívánt indexű pin.
     * @return OutputPin* Az adott indexű pin.
     * @exception std::out_of_range = ha túlindexelünk.
     */
    OutputPin* getOutputPinByIndex(size_t idx);

    /**
     * @brief Beállítja a kimeneti csomópont ID-t kiolvasáshoz.
     *
     * @param at A beállított kimenet indexe.
     * @param ID A beállított csomópont ID.
     * @exception std::out_of_range = ha túlindexelünk.
     */
    void setOutputNodeID(size_t at, size_t ID);

    /**
     * @brief Ellenőri, hogy kapcsolódik-e egy adott csomóponthoz a kimenetén.
     *
     * @param ID A keresett csomópont ID-ja.
     * @return true = kapcsolódik hozzá a kimeneten ;
     * @return false = nem kapcsolódik hozzá a kimeneten
     */
    bool isConnectedToNodeOnOutput(size_t ID);

    /**
     * @brief Kiírja a kimeneten csatlakoztatott csomópontok ID-ját.
     *
     * @param os A kimeneti stream, ahova akarjuk kiírni.
     */
    void printConnectedOutputNodes(std::ostream& os) const;

    /**
     * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
     *
     */
    virtual void executeFunction() = 0;

    /**
     * @brief Törli a kimeneti pin-ek tömbjét.
     *
     */
    virtual ~OutputComponent();
};



#endif // OUTPUTCOMPONENT_H_