#ifndef IOCOMPONENT_H_
#define IOCOMPONENT_H_

#include "InputComponent.h"
#include "OutputComponent.h"
#include "memtrace.h"


class IOComponent : public InputComponent, public OutputComponent {
public:
    /**
     * @brief Létrehozza az IO elemet, mindkét oldali tulajdonságaival.
     *
     * @param inputCount Bemeneti lábak száma.
     * @param outputCount Kimeneti lábak száma.
     */
    IOComponent(size_t inputCount, size_t outputCount);

    /**
     * @brief Ellenőrzi, hogy kapcsolódik-e két csomóponthoz ellentétes oldalról (egyik kimeneti, másik bemeneti, vagy fordítva).
     *
     * @param NodeID1 Az egyik csomópont ID-ja.
     * @param NodeID2 A másik csomópont ID-ja.
     * @return true = kapcsolódik ezekhez ;
     * @return false = nem kapcsolódik ezekhez
     */
    bool isConnectedToNodes(size_t NodeID1, size_t NodeID2);

    /**
     * @brief Kiírja a kapcsolódó csomópontok ID-jait mind bemenet, mind kimenetre (előbb bemenet, utána kimenet).
     *
     * @param os A kimeneti stream, ahova akarjuk kiírni.
     */
    void printConnectedNodes(std::ostream& os) const;

    /**
     * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
     *
     */
    virtual void executeFunction() = 0;

    /**
     * @brief Virtuális destruktor, mert öröklés.
     *
     */
    virtual ~IOComponent();
};


#endif // IOCOMPONENT_H_