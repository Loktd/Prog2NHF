#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Pin.h"
#include "Queue.h"

typedef long long unsigned int size_t;

class Component {
protected:
  /**
   * @brief Az aktív sor, amihez kell hozzáadni, ha ki kell értékelni az elemet, azaz végrehajtani a funkcióját.
   */
  Queue<Component>* activeQueue;

public:
  /**
   * @brief Felparaméterezi az aktív sort.
   *
   * @param newActiveQueue A kívánt aktív sor.
   */
  Component(Queue<Component>* newActiveQueue = nullptr) : activeQueue(newActiveQueue) {}

  /**
   * @brief Beállítja az aktív fifo-t.
   *
   */
  void setActiveQueue(Queue<Component>* newActiveQueue) { activeQueue = newActiveQueue; }

  /**
   * @brief Hozzáadja az aktív sorhoz az áramköri elemet.
   *
   */
  void addToActiveQueue();

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  /**
   * @brief Virtuális destruktor öröklés miatt.
   *
   */
  virtual ~Component() {}

};
class InPin_Component : virtual public Component {
protected:
  /**
   * @brief A bemeneti pin-ek száma.
   */
  size_t inPinCount;
  /**
   * @brief Az aktív, valid adattal rendelkező pin-ek száma.
   */
  size_t activeInPins;
  /**
   * @brief A bemeneti pin-ek tömbje. Az index jelentést a specifikált alkatrész adja meg.
   */
  InPin* inPins;

public:
  /**
   * @brief Létrehozza a bemeneti pin-ek tömbjét.
   *
   * @param inCount A bemeneti pin-ek száma.
   */
  InPin_Component(size_t inCount);

  /**
   * @brief Reseteli az aktív pin-ek számát 0-ra.
   *
   */
  void resetActiveCount() { activeInPins = 0; }

  /**
   * @brief Növeli az aktív lábak számát, és aktivizálja az áramköri elemet, ha eléri a maximumot.
   *
   */
  void tickCounter();

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  /**
   * @brief Törli a bemeneti pin-ek tömbjét.
   *
   */
  virtual ~InPin_Component() { delete[] inPins; }

};
class OutPin_Component : virtual public Component {
protected:
  /**
   * @brief A kimeneti pin-ek száma.
   */
  size_t outPinCount;
  /**
   * @brief A kimeneti pin-ek tömbje.  Az index jelentést a specifikált alkatrész adja meg.
   *
   */
  OutPin* outPins;

public:
  /**
   * @brief Létrehozza a kimeneti pin-ek tömbjét.
   *
   * @param outCount A kívánt kimeneti pin-ek száma.
   */
  OutPin_Component(size_t outCount);

  /**
   * @brief Kiküldi minden kimeneti lábán a lábakban tárolt jeleket.
   *
   */
  void sendOutSignals();

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  /**
   * @brief Törli a kimeneti pin-ek tömbjét.
   *
   */
  virtual ~OutPin_Component() { delete[] outPins; }

};
class IOPin_Component : public InPin_Component, public OutPin_Component {
public:
  /**
   * @brief Lértehozza a lábakat.
   *
   * @param inCount Bemeneti lábak száma.
   * @param outCount Kimeneti lábak száma.
   */
  IOPin_Component(size_t inCount, size_t outCount) : InPin_Component(inCount), OutPin_Component(outCount) {}

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  /**
   * @brief Virtuális destruktor, mert öröklés.
   *
   */
  virtual ~IOPin_Component() {}
};
#endif
