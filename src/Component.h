#ifndef _COMPONENT_H
#define _COMPONENT_H


#include "Pin.h"

template<class T> class Queue;

class Component {
protected:

public:
  void addToActiveQueue(const Queue<Component>& activeQueue);

  virtual void executeFunction() = 0;

  virtual ~Component() {}

};
class InPin_Component : virtual public Component {
protected:
  int notReadyCounter;

  int inPinCount;

  Pin inPins;
  int activeInPins;


public:
  void tickCounter();
  void checkIfReady();

  virtual void executeFunction() = 0;

  virtual ~InPin_Component() {}

};
class OutPin_Component : virtual public Component {
protected:
  int outPinCount;

  Pin outPins;

public:
  virtual void executeFunction() = 0;

  virtual ~OutPin_Component() {}

};
class IOPin_Component : public InPin_Component, public OutPin_Component {
public:
  virtual void executeFunction() = 0;

  virtual ~IOPin_Component() {}

};
#endif
