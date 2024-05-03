
#include "Pin.h"
#include "Component.h"
#include "Node.h"

#include <string>


// Pin kezdet

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

// Pin vége


// InputPin kezdet

InputPin::InputPin(Signal baseSignal) : Pin(baseSignal), component(nullptr), ready(false) {}

void InputPin::connenctToComponent(InputComponent* connected)
{
    component = connected;
}

InputComponent* InputPin::getComponent() const
{
    return component;
}

bool InputPin::isReady()
{
    return ready;
}

void InputPin::setReady()
{
    if (component == nullptr) {
        throw "ERROR: An input pin doesn't have an associated component...";
    }

    ready = true;
    component->activateIfReady();
}

void InputPin::resetReady()
{
    ready = false;
}

InputPin::~InputPin()
{
}

// InputPin vége


// OutputPin kezdet

OutputPin::OutputPin(Signal baseSignal) : Pin(baseSignal), connectedTo(nullptr) {}

void OutputPin::connectToPin(InputPin* pin)
{
    connectedTo = pin;
}

void OutputPin::sendSignal() const
{
    if (connectedTo == nullptr) {
        throw "ERROR: An output pin doesn't have an associated input pin...";
    }
    if (!connectedTo->isReady()) {
        connectedTo->setSignal(ownedSignal);
        connectedTo->setReady();
    }
    else if (connectedTo->getSignal() != ownedSignal) {
        throw std::string("ERROR: Shortcircuit");
    }
}

OutputPin::~OutputPin()
{
}

// OutputPin vége