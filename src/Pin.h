#ifndef _PIN_H
#define _PIN_H


class Component;

class Pin {
  private:
    Signal ownedSignal;

    Pin* connectedTo;

    Component* component;


  public:
    Pin(const Signal & signal, const Pin* & connection, const Component* & component);

    void connectWith(const Pin* & other);

    void sendOutSingal() const;

    void setSignal(const Signal & newSignal);

    void signalReady() const;

};
class Signal {
  private:
    bool signal;


  public:
    Signal(bool baseValue = false);

    void setSignal(bool newValue);

    bool getSignal() const;

    void flipSignal();

};
#endif
