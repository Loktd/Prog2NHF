#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "Component.h"

#include <iostream>


class Source : public OutputComponent {
public:
    /**
     * @brief Létrehoz egy forrást.
     *
     */
    Source();

    /**
     * @brief Végrehajtja a forrás funkcióját, azaz kiküldi a jelet a kimenetén.
     *
     */
    virtual void executeFunction();

    /**
     * @brief Beállítja a forrás kimeneti jelét.
     *
     * @param signal Az új jel.
     */
    void setOutput(const Signal& signal);

    /**
     * @brief Visszaadja a forrás kimeneti jelét.
     *
     * @return A forrás jele.
     */
    Signal getOutput() const;

    /**
     * @brief Megfordítja a kimeneti jel értékét.
     *
     */
    void flipOutput();

    /**
     * @brief Virtuális destruktor öröklés miatt.
     *
     */
    virtual ~Source() {}
};

/**
 * @brief Kiírja a forrás jelét a kimeneti streamre.
 *
 * @param os A kimeneti stream.
 * @param x A forrás, amit ki kell írni.
 * @return A kimeneti stream-re referencia, a láncolás miatt.
 */
std::ostream& operator<<(std::ostream& os, const Source& x);

/**
 * @brief A kapcsolót megvalósító osztály, állítható hogy zárt vagy nyílt-e, ennek függvényében
 * @brief vagy adja tovább a bemeneti jelet ha zárva, vagy LOW jelszintet ha nyitva van.
 *
 */
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


class Lamp : public InputComponent {
public:
    /**
     * @brief Létrehoz egy lámpát.
     *
     */
    Lamp();

    /**
     * @brief Visszaadja a lámpa jelét, azaz, hogy világít-e.
     *
     * @return A jelérték.
     */
    Signal getState() const;

    /**
     * @brief Itt igazából haszontalan, lámpának nincs végezni valója.
     *
     */
    virtual void executeFunction();

    /**
     * @brief Virtuális destruktor az öröklés miatt.
     *
     */
    virtual ~Lamp();
};

/**
 * @brief Kiírja a kimeneti streamre a lámpa jelének értékét.
 *
 * @param os A kimeneti stream.
 * @param x A kiírt lámpa.
 * @return A kimeneti stream-re referencia, láncolás miatt.
 */
std::ostream& operator<<(std::ostream& os, const Lamp& x);

#endif // PERIPHERALS_H_