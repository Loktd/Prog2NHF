#ifndef _COMPONENT_H
#define _COMPONENT_H


class Pin;

class Component {
  private:
    bool canExecute;


  public:
    virtual void executeFunction() = 0;

    virtual ~Component();

};
class InPin_Component : public Component {
  private:
    int inPinCount;

    Pin* inPins;

    int activeInPins;


  public:
    virtual ~InPin_Component();

};
class IOPin_Component : public InPin_Component, public OutPin_Component {
  public:
    virtual ~IOPin_Component();

};
class OutPin_Component : public Component {
  private:
    int outPinCount;

    Pin* outPins;


  public:
    virtual ~OutPin_Component();

};
#endif
