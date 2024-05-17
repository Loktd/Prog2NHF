#ifndef _PIN_H
#define _PIN_H

#include "Signal.hpp"


class Pin {
protected:
  /**
   * @brief A pin által birtokolt jel.
   *
   */
  Signal ownedSignal;
public:
  /**
   * @brief Létrehoz egy pin-t kezdő jelértékkel.
   *
   * @param baseSignal Az alap jelérték, default-ként LOW (0) jelszinttel.
   */
  Pin(Signal baseSignal = Signal(false));

  /**
   * @brief Beállítja a pin jelét.
   *
   * @param newSignal Az új jel.
   */
  void setSignal(const Signal& newSignal);

  /**
   * @brief Visszaadja a pin jelét. Mivel kicsi a Signal osztály, ezért nem kell pointer/referencia.
   *
   * @return A visszaadott jel.
   */
  Signal getSignal() const;

  /**
   * @brief Megfordítja a pin jelét.
   *
   */
  void flipSignal();

  /**
   * @brief Virtuális a destruktor az öröklés miatt.
   *
   */
  virtual ~Pin();
};

#endif