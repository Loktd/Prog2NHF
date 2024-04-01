
#include "Pin.h"
#include "Component.h"

void Pin::sendOutSingal() const {
    if (connectedTo == nullptr) {
        throw "No connection...";
    }
    if (connectedTo->ofComponent == nullptr) {
        throw "Target pin doesn't have an associated component..";
    }
    connectedTo->setSignal(ownedSignal);
    connectedTo->signalReadyToComponent();
}

void Pin::signalReadyToComponent() const {
    if (ofComponent == nullptr) {
        throw "Pin doesn't have a component...";
    }
    ofComponent->checkIfReady();
}

