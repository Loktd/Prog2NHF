
#include "Component.h"
#include "Queue.h"

#include <string>
#include <iostream>

typedef long long unsigned int size_t;

InputComponent::InputComponent(size_t inCount)
{
    inPinCount = inCount;
    activeInPins = 0;
    inPins = new InputPin[inPinCount];
    inNodeIDs = new size_t[inPinCount];
    for (size_t i = 0; i < inPinCount; i++) {
        inPins[i].connenctToComponent(this);
    }
}

void InputComponent::setInNodeID(size_t at, size_t id)
{
    if (at >= inPinCount) {
        throw std::string("Indexed out of inNodeID range...\n");
    }
    inNodeIDs[at] = id;
}

bool InputComponent::connectedToNodeIn(size_t id)
{
    for (size_t i = 0; i < inPinCount; i++) {
        if (inNodeIDs[i] == id) {
            return true;
        }
    }
    return false;
}

void InputComponent::printInConnectedNodes(std::ostream& os) const
{
    for (size_t i = 0; i < inPinCount; i++) {
        os << inNodeIDs[i];
        if (i != inPinCount - 1)
            os << " ";
    }
}

void InputComponent::resetForSimulation()
{
    activeInPins = 0;
}

void InputComponent::tickCounter()
{
    activeInPins++;
    if (activeInPins == inPinCount) {
        addToActiveQueue();
    }
    else if (activeInPins > inPinCount) {
        std::cout << this << activeInPins << std::endl;
    }
}

InputComponent::~InputComponent()
{
    delete[] inPins;
    delete[] inNodeIDs;
}

OutputComponent::OutputComponent(size_t outCount)
{
    outPinCount = outCount;
    outPins = new OutputPin[outPinCount];
    outPinIDs = new size_t[outPinCount];
}

void OutputComponent::connectTo(size_t outPinIndex, InputComponent* component, size_t inPinIndex)
{
    outPins[outPinIndex].connectToPin(component->getInPinsBaseAdress() + inPinIndex);
}

void OutputComponent::sendOutSignals()
{
    for (size_t i = 0; i < outPinCount; i++) {
        outPins[i].sendSignal();
    }
}

void OutputComponent::setOutNodeID(size_t at, size_t id)
{
    if (at >= outPinCount) {
        throw std::string("Indexed out of outNodeID range...");
    }
    outPinIDs[at] = id;
}

bool OutputComponent::connectedToNodeOut(size_t id)
{
    for (size_t i = 0; i < outPinCount; i++) {
        if (outPinIDs[i] == id)
            return true;
    }
    return false;
}

void OutputComponent::printOutConnectedNodes(std::ostream& os) const
{
    for (size_t i = 0; i < outPinCount; i++) {
        os << outPinIDs[i];
        if (i != outPinCount - 1)
            os << " ";
    }
}

OutputComponent::~OutputComponent()
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

bool IOComponent::connectedToNodes(size_t connectedNode1, size_t connectedNode2)
{
    return connectedToNodeIn(connectedNode1) && connectedToNodeOut(connectedNode2) || connectedToNodeIn(connectedNode2) && connectedToNodeOut(connectedNode1);
}

void IOComponent::printConnectedNodes(std::ostream& os) const
{
    printInConnectedNodes(os);
    os << " and ";
    printOutConnectedNodes(os);
}
