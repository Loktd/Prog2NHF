#ifndef _PIN_H
#define _PIN_H


#include "Signal.h"

class Component;

class Pin {
  Signal ownedSignal;
  Pin* connectedTo;

  Component* ofComponent;


public:
  Pin() : ownedSignal(Signal(false)), connectedTo(nullptr), ofComponent(nullptr) {}

  void connectWithPin(Pin* other) { connectedTo = other; }

  void connectWithCompononet(Component* component) { ofComponent = component; }

  void sendOutSingal() const;

  void setSignal(const Signal& newSignal) { ownedSignal = newSignal; }

  void signalReadyToComponent() const;

};
#endif
