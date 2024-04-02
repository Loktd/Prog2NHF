#ifndef _SWITCH_H
#define _SWITCH_H

#include "Component.h"

#include <iostream>

class Switch : public IOPin_Component {
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
  Switch() : IOPin_Component(1, 1), closed(false) {}

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
  bool getState() const { return closed; }

  /**
   * @brief Átbillenti másik állapotba a kapcsolót.
   *
   */
  void flipState() { closed = !closed; }

  virtual ~Switch() {}
};

/**
 * @brief Kiírja a kimeneti stream-re a kapcsoló állását.
 *
 * @param os A kimeneti stream.
 * @param x A kapcsoló.
 * @return Kimeneti stream-re referencia, láncolás miatt.
 */
std::ostream& operator<<(std::ostream& os, const Switch& x);
#endif
