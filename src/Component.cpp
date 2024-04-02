
#include "Component.h"
#include "Queue.h"

typedef long long unsigned int size_t;

InPin_Component::InPin_Component(size_t inCount)
{
    inPinCount = inCount;
    activeInPins = 0;
    inPins = new InPin[inPinCount];
    for (size_t i = 0; i < inPinCount; i++) {
        inPins[i].connenctToComponent(this);
    }
}

void InPin_Component::tickCounter()
{
    activeInPins++;
    if (activeInPins == inPinCount) {
        addToActiveQueue();
    }
    else if (activeInPins > inPinCount) {
        throw "ERROR: Recursion...";
    }
}

OutPin_Component::OutPin_Component(size_t outCount)
{
    outPinCount = outCount;
    outPins = new OutPin[outPinCount];
}

void OutPin_Component::connectTo(size_t outPinIndex, InPin_Component* component, size_t inPinIndex)
{
    outPins[outPinIndex].connectToPin(component->getInPinsBaseAdress() + inPinIndex);
}

void OutPin_Component::sendOutSignals()
{
    for (size_t i = 0; i < outPinCount; i++) {
        outPins[i].sendSignal();
    }
}

void Component::addToActiveQueue()
{
    if (activeQueue == nullptr)
        throw "This component doesn't have an active queue...";
    activeQueue->put(this);
}
