
#include "Pin.h"
#include "Component.h"

Pin::Pin(Signal baseSignal) : ownedSignal(baseSignal) {}

void Pin::setSignal(const Signal& newSignal)
{
    ownedSignal = newSignal;
}

Signal Pin::getSignal() const
{
    return ownedSignal;
}

void Pin::flipSignal()
{
    ownedSignal.flip();
}

InputPin::InputPin(Signal baseSignal) : Pin(baseSignal), component(nullptr), ready(false) {}

void InputPin::connenctToComponent(InputComponent* connected)
{
    component = connected;
}

InputComponent* InputPin::getComponent() const
{
    return component;
}

void InputPin::SignalReady() const
{
    if (component == nullptr) {
        throw "ERROR: An input pin doesn't have an associated component...";
    }
    component->tickCounter();
}

void OutputPin::sendSignal() const
{
    if (connectedTo == nullptr) {
        throw "ERROR: An output pin doesn't have an associated input pin...";
    }
    connectedTo->setSignal(ownedSignal);
    connectedTo->SignalReady();
}
