#ifndef _PIN_H
#define _PIN_H

#include "Signal.h"
#include "Exceptions.h"

typedef long long unsigned int size_t;

class InputComponent;
class OutputComponent;

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
  virtual ~Pin() {}
};

class InputPin : public Pin {
  /**
   * @brief Az áramköri elem, melynek része a bemeneti pin.
   *
   */
  InputComponent* component;
  /**
   * @brief Tárolja, hogy készen áll a pin feldolgozásra.
   *
   */
  bool ready;
public:
  /**
   * @brief Létrehoz egy bemeneti pin-t, komponensét NULL-ra állítva.
   *
   * @param baseSignal Az alapjel, ha van megadva.
   */
  InputPin(Signal baseSignal = Signal(false));

  /**
   * @brief Egy áramköri elemhez köti a bemeneti pin-t, így tud majd neki üzenni.
   *
   * @param component Az áramköri elem, amihez kötjük.
   */
  void connenctToComponent(InputComponent* connected);

  /**
   * @brief Visszaadja a pointerét arra az elemre, amihez kapcsolódik.
   *
   * @return Az elem, aminek része.
   */
  InputComponent* getComponent() const;

  /**
   * @brief Visszaadja, hogy készen áll-e kiértékelésre a bemeneti pin, azaz erről a pinről már meg van-e a helyes bemenet.
   *
   * @return true = ha készenáll.
   * @return false = ha még nem áll készen
   */
  bool isReady();

  /**
   * @brief Jelzi az áramköri elem felé, hogy ezen a lábán rendelkezésre áll a jel.
   *
   * @exception const char* = amennyiben nincs hozzá kötve áramköri elem.
   */
  void setReady();

  /**
   * @brief Reseteli a készenlétet, azaz a pin-nek beállítja, hogy még nem áll készen adat feldolgozásra.
   *
   */
  void resetReady();

  /**
   * @brief Virtuális a destruktor az öröklés miatt.
   *
   */
  virtual ~InputPin();
};

class OutputPin : public Pin {
  /**
   * @brief A bemeneti pin, amihez van kapcsolva.
   *
   */
  InputPin* connectedTo;
public:
  /**
   * @brief Létrhoz egy kimeneti pin-t, kapcsolt bemeneti pin-jét NULL-ra állítva.
   *
   * @param baseSignal Az alapjel, ha van megadva.
   */
  OutputPin(Signal baseSignal = Signal(false));

  /**
   * @brief Összekapcsolja egy bemeneti pin-nel.
   *
   * @param pin A kapcsolni kívánt pin.
   */
  void connectToPin(InputPin* pin);

  /**
   * @brief Jelet küld a kapcsolt bemeneti pin-nek.
   *
   * @exception const char* = amennyiben nincs hozzá kötve bemeneti pin.
   */
  void sendSignal() const;

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   * 
   */
  virtual ~OutputPin();
};
#endif
