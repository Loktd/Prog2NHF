
#include "Component.h"
#include "Queue.h"

#include <string>
#include <iostream>

typedef long long unsigned int size_t;

InPin_Component::InPin_Component(size_t inCount)
{
    inPinCount = inCount;
    activeInPins = 0;
    inPins = new InPin[inPinCount];
    inNodeIDs = new size_t[inPinCount];
    for (size_t i = 0; i < inPinCount; i++) {
        inPins[i].connenctToComponent(this);
    }
}

void InPin_Component::setInNodeID(size_t at, size_t id)
{
    if (at >= inPinCount) {
        throw std::string("Indexed out of inNodeID range...\n");
    }
    inNodeIDs[at] = id;
}

bool InPin_Component::connectedToNodeIn(size_t id)
{
    for (size_t i = 0; i < inPinCount; i++) {
        if (inNodeIDs[i] == id) {
            return true;
        }
    }
    return false;
}

void InPin_Component::printInConnectedNodes(std::ostream& os) const
{
    for (size_t i = 0; i < inPinCount; i++) {
        os << inNodeIDs[i];
        if (i != inPinCount - 1)
            os << " ";
    }
}

void InPin_Component::resetForSimulation()
{
    activeInPins = 0;
}

void InPin_Component::tickCounter()
{
    activeInPins++;
    if (activeInPins == inPinCount) {
        addToActiveQueue();
    }
    else if (activeInPins > inPinCount) {
        std::cout << this << activeInPins << std::endl;
        throw "ERROR: Recursion...";
    }
}

InPin_Component::~InPin_Component()
{
    delete[] inPins;
    delete[] inNodeIDs;
}

OutPin_Component::OutPin_Component(size_t outCount)
{
    outPinCount = outCount;
    outPins = new OutPin[outPinCount];
    outPinIDs = new size_t[outPinCount];
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

void OutPin_Component::setOutNodeID(size_t at, size_t id)
{
    if (at >= outPinCount) {
        throw std::string("Indexed out of outNodeID range...");
    }
    outPinIDs[at] = id;
}

bool OutPin_Component::connectedToNodeOut(size_t id)
{
    for (size_t i = 0; i < outPinCount; i++) {
        if (outPinIDs[i] == id)
            return true;
    }
    return false;
}

void OutPin_Component::printOutConnectedNodes(std::ostream& os) const
{
    for (size_t i = 0; i < outPinCount; i++) {
        os << outPinIDs[i];
        if (i != outPinCount - 1)
            os << " ";
    }
}

OutPin_Component::~OutPin_Component()
{
    delete[] outPins;
    delete[] outPinIDs;
}

void Component::addToActiveQueue()
{
    if (activeQueue == nullptr)
        throw "This component doesn't have an active queue...";
    activeQueue->put(this);
}

bool IOPin_Component::connectedToNodes(size_t connectedNode1, size_t connectedNode2)
{
    return connectedToNodeIn(connectedNode1) && connectedToNodeOut(connectedNode2) || connectedToNodeIn(connectedNode2) && connectedToNodeOut(connectedNode1);
}

void IOPin_Component::printConnectedNodes(std::ostream& os) const
{
    printInConnectedNodes(os);
    os << " and ";
    printOutConnectedNodes(os);
}
