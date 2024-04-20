#ifndef _SIGNAL_H
#define _SIGNAL_H

typedef long long unsigned int size_t;

class Signal {
  /**
   * @brief A tárolt jelérték.
   * @brief false = LOW (0) jel, true = HIGH (1) jel
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
  void setValue(bool newValue) { signal = newValue; }

  /**
   * @brief Visszaadja a jel értékét.
   *
   * @return true = 1 a jelérték.
   * @return false = 0 a jelérték.
   */
  bool getValue() const { return signal; }

  /**
   * @brief Megfordítja a jelértéket.
   *
   */
  void flip() { signal = !signal; }

  /**
   * @brief Egyenlőséget vizsgálja két jelszint között.
   *
   * @param other A másik jel amivel hasonlítunk.
   * @return true, ha egyeznek.
   * @return false, ha nem egyeznek
   */
  bool operator==(const Signal& other) { return signal == other.signal; }
};

#endif
