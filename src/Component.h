#ifndef _COMPONENT_H
#define _COMPONENT_H


#include "Pin.h"

template<class T> class Queue;

class Component {
protected:
  Queue<Component>* activeQueue;

public:
  Component(Queue<Component>* newActiveQueue) : activeQueue(newActiveQueue) {}

  void addToActiveQueue() const { activeQueue->put(this); }

  virtual void executeFunction() = 0;

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
