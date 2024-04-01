#ifndef _SIGNAL_H
#define _SIGNAL_H

typedef long long unsigned int size_t;

class Signal {
  /**
   * @brief A tárolt jelérték. (0 = false, 1 = true)
   */
  bool signal;

public:
  /**
   * @brief Létrehozza a jel objektumot, adott értékkel, ha van.
   *
   * @param baseValue Az alapérték.
   */
  Signal(bool baseValue = false) : signal(baseValue) {}

  /**
   * @brief Beállítja egy új értékre a jelet.
   *
   * @param newValue Az új jel értéke.
   */
  void setSignal(bool newValue) { signal = newValue; }
  /**
   * @brief Visszaadja a jel értékét.
   *
   * @return true = 1 a jelérték.
   * @return false = 0 a jelérték.
   */
  bool getSignal() const { return signal; }

  /**
   * @brief Megfordítja a jelértéket.
   *
   */
  void flipSignal() { signal = !signal; }
};
#endif
