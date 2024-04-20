#ifndef _SOURCE_H
#define _SOURCE_H

#include "Component.h"

#include <iostream>

class Source : public OutputComponent {
public:
  /**
   * @brief Létrehoz egy forrást.
   */
  Source();

  /**
   * @brief Végrehajtja a forrás funkcióját, azaz kiküldi a jelet a kimenetén.
   *
   */
  virtual void executeFunction() { sendOutSignals(); }

  /**
   * @brief Beállítja a forrás kimeneti jelét.
   *
   * @param signal Az új jel.
   */
  void setOutput(const Signal& signal) { outPins[0].setSignal(signal); }

  /**
   * @brief Visszaadja a forrás kimeneti jelét.
   *
   * @return A forrás jele.
   */
  Signal getOutput() const { return outPins[0].getSignal(); }

  /**
   * @brief Megfordítja a kimeneti jel értékét.
   *
   */
  void flipOutput() { outPins[0].flipSignal(); }

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
#endif
