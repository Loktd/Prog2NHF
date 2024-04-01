
#include "Pin.h"
#include "Component.h"

void InPin::SignalReady() const
{
    if (ofComponent == nullptr) {
        throw "ERROR: An input pin doesn't have an associated component...";
    }
    ofComponent->tickCounter();
}

void OutPin::sendSignal() const
{
    if (connectedTo == nullptr) {
        throw "ERROR: An output pin doesn't have an associated input pin...";
    }
    connectedTo->setSignal(ownedSignal);
    connectedTo->SignalReady();
}
