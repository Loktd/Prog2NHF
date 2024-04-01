
#include "Pin.h"
#include "Component.h"

void InPin::SignalReady() const
{
    if (ofComponent == nullptr) {
        throw "ERROR: This input pin doesn't have an associated component...";
    }
    ofComponent->tickCounter();
}

void OutPin::sendSignal() const
{
    if (connectedTo == nullptr) {
        throw "ERROR: This output pin doesn't have an associated input pin...";
    }
    connectedTo->setSignal(ownedSignal);
    connectedTo->SignalReady();
}
