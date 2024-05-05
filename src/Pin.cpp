#include "Pin.h"


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

Pin::~Pin() {}

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
        throw NonExistentConnection("ERROR: An InputPin doesn't have a connected component while sending a message...\n");
    }

    ready = true;
    component->activateIfReady();
}

void InputPin::resetReady()
{
    ready = false;
}

InputPin::~InputPin() {}

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
        throw NonExistentConnection("ERROR: An OutputPin doesn't have an associated input pin when sending message...\n");
    }
    if (connectedTo->isReady()) {
        throw ShortCircuit("ERROR: Shortcircuit from looping back...\n");
    }

    connectedTo->setSignal(ownedSignal);
    connectedTo->setReady();
}

OutputPin::~OutputPin() {}

// OutputPin vége