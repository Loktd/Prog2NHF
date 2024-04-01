#ifndef _PIN_H
#define _PIN_H


#include "Signal.h"

class InPin_Component;
class OutPin_Component;

class Pin {
protected:
  Signal ownedSignal;
public:
  Pin(Signal baseSignal = Signal(false)) { ownedSignal = baseSignal; }

  void setSignal(const Signal& newSignal) { ownedSignal = newSignal; }
  Signal getSignal() const { return ownedSignal; }

  virtual ~Pin() {}
};

class InPin : public Pin {
  InPin_Component* ofComponent;
public:
  InPin(Signal baseSignal = Signal(false)) : Pin(baseSignal), ofComponent(nullptr) {}

  void connenctToComponent(InPin_Component* component) { ofComponent = component; }
  void SignalReady() const;
};

class OutPin : public Pin {
  InPin* connectedTo;
public:
  OutPin(Signal baseSignal = Signal(false)) : Pin(baseSignal), connectedTo(nullptr) {}

  void connectToPin(InPin* pin) { connectedTo = pin; }
  void sendSignal() const;
};
#endif
