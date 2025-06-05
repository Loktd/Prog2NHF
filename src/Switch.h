#ifndef SWITCH_H_
#define SWITCH_H_

#include "IOComponent.h"
#include <iostream>
#include "memtrace.h"


class Switch : public IOComponent {
    /**
     * @brief Zárva van-e a kapcsoló (true = zárt, false = nyitott)
     *
     */
    bool closed;
public:
    /**
     * @brief Létrehozza a kapcsolót.
     *
     */
    Switch();

    /**
     * @brief Megvalósítja a kapcsolót, azaz ha zárt akkor a bemeneti jelet továbbítja, egyébként meg LOW (0) jelet ad.
     *
     */
    virtual void executeFunction();

    /**
     * @brief Vissza adja hogy zárt-e a kapcsoló.
     *
     * @return true = zárt,
     * @return false = nyitott
     */
    bool getState() const;

    /**
     * @brief Beállítja a kapcsoló állapotát.
     *
     * @param newState Az új állapot. (true = zárt, false = nyitott)
     */
    void setState(bool newState);

    /**
     * @brief Átbillenti másik állapotba a kapcsolót.
     *
     */
    void flipState();

    /**
     * @brief Virtuális destruktor az öröklés miatt.
     *
     */
    virtual ~Switch();
};

/**
 * @brief Kiírja a kimeneti stream-re a kapcsoló állását.
 *
 * @param os A kimeneti stream.
 * @param x A kapcsoló.
 * @return Kimeneti stream-re referencia, láncolás miatt.
 */
std::ostream& operator<<(std::ostream& os, const Switch& x);


#endif // SWITCH_H_