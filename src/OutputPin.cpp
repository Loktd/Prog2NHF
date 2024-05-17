#include "OutputPin.h"

OutputPin::OutputPin(Signal baseSignal) : Pin(baseSignal), connectedTo(nullptr) {}

void OutputPin::connectToPin(InputPin* pin)
{
    connectedTo = pin;
}

void OutputPin::sendSignal() const
{
    if (connectedTo == nullptr) {
        throw NonExistentConnection("An OutputPin doesn't have an associated input pin when sending message...");
    }
    if (connectedTo->isReady()) {
        if (connectedTo->getSignal() != ownedSignal)
            throw ShortCircuit("Shortcircuit from looping back", connectedTo->getComponent());
        else
            return;
    }
    connectedTo->setSignal(ownedSignal);
    connectedTo->setReady();
}

OutputPin::~OutputPin() {}