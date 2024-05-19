#ifndef LAMP_H_
#define LAMP_H_

#include "InputComponent.h"
#include <iostream>
#include "../test/memtrace.h"


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

#endif // LAMP_H_