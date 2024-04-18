#ifndef _PIN_H
#define _PIN_H

#include "Signal.h"

typedef long long unsigned int size_t;

class InPin_Component;
class OutPin_Component;

class Pin {
protected:
  /**
   * @brief A pin által birtokolt jel.
   */
  Signal ownedSignal;
public:
  /**
   * @brief Létrehoz egy pin-t kezdő jelértékkel.
   *
   * @param baseSignal Az alap jelérték.
   */
  Pin(Signal baseSignal = Signal(false)) { ownedSignal = baseSignal; }

  /**
   * @brief Beállítja a pin jelét.
   *
   * @param newSignal Az új jel.
   */
  void setSignal(const Signal& newSignal) { ownedSignal = newSignal; }

  /**
   * @brief Visszaadja a pin jelét. Mivel kicsi a Signal osztály, ezért nem kell pointer/referencia.
   *
   * @return A visszaadott jel.
   */
  Signal getSignal() const { return ownedSignal; }

  /**
   * @brief Megfordítja a pin jelét.
   *
   */
  void flipSignal() { ownedSignal.flipSignal(); }

  /**
   * @brief Virtuál destruktor, mert öröklés.
   *
   */
  virtual ~Pin() {}
};

class InPin : public Pin {
  /**
   * @brief Az áramköri elem, melynek része a bemeneti pin.
   */
  InPin_Component* ofComponent;
public:
  /**
   * @brief Létrhoz egy bemeneti pin-t, komponensét NULL-ra állítva.
   *
   * @param baseSignal Az alapjel, ha van megadva.
   */
  InPin(Signal baseSignal = Signal(false)) : Pin(baseSignal), ofComponent(nullptr) {}

  /**
   * @brief Egy áramköri elemhez köti a bemeneti pin-t, így tud majd neki üzenni.
   *
   * @param component Az áramköri elem, amihez kötjük.
   */
  void connenctToComponent(InPin_Component* component) { ofComponent = component; }

  InPin_Component* getComponent() const { return ofComponent; }

  /**
   * @brief Jelzi az áramköri elem felé, hogy ezen a lábán rendelkezésre áll a jel.
   *
   * @exception const char* = amennyiben nincs hozzá kötve áramköri elem.
   */
  void SignalReady() const;
};

class OutPin : public Pin {
  /**
   * @brief A bemeneti pin, amihez van kapcsolva.
   */
  InPin* connectedTo;
public:
  /**
   * @brief Létrhoz egy kimeneti pin-t, kapcsolt bemeneti pin-jét NULL-ra állítva.
   *
   * @param baseSignal Az alapjel, ha van megadva.
   */
  OutPin(Signal baseSignal = Signal(false)) : Pin(baseSignal), connectedTo(nullptr) {}

  /**
   * @brief Összekapcsolja egy bemeneti pin-nel.
   *
   * @param pin A kapcsolni kívánt pin.
   */
  void connectToPin(InPin* pin) { connectedTo = pin; }
  /**
   * @brief Jelet küld a kapcsolt bemeneti pin-nek.
   *
   * @exception const char* = amennyiben nincs hozzá kötve bemeneti pin.
   */
  void sendSignal() const;
};
#endif
