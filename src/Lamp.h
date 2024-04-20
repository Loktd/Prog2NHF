#ifndef _LAMP_H
#define _LAMP_H

#include "Component.h"

#include <iostream>

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
  Signal getState() const { return inPins[0].getSignal(); }

  /**
   * @brief Itt igazából haszontalan, lámpának nincs végezni valója.
   *
   */
  virtual void executeFunction() {}

  virtual ~Lamp() {}
};

/**
 * @brief Kiírja a kimeneti streamre a lámpa jelének értékét.
 *
 * @param os A kimeneti stream.
 * @param x A kiírt lámpa.
 * @return A kimeneti stream-re referencia, láncolás miatt.
 */
std::ostream& operator<<(std::ostream& os, const Lamp& x);
#endif
