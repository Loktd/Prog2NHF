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
  Component(Queue<Component>* newActiveQueue) : activeQueue(newActiveQueue) {}

  /**
   * @brief Hozzáadja az aktív sorhoz az áramköri elemet.
   *
   */
  void addToActiveQueue() { activeQueue->put(this); }

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
  size_t inPinCount;
  size_t activeInPins;
  InPin* inPins;

public:
  InPin_Component(size_t inCount);

  void resetActiveCount() { activeInPins = 0; }
  void tickCounter();

  virtual void executeFunction() = 0;

  virtual ~InPin_Component() { delete[] inPins; }

};
class OutPin_Component : virtual public Component {
protected:
  size_t outPinCount;

  OutPin* outPins;

public:
  OutPin_Component(size_t outCount);

  void sendOutSignals();

  virtual void executeFunction() = 0;

  virtual ~OutPin_Component() { delete[] outPins; }

};
class IOPin_Component : public InPin_Component, public OutPin_Component {
public:
  virtual void executeFunction() = 0;

  virtual ~IOPin_Component() {}
};
#endif
