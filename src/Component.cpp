#include "Component.h"
#include "Queue.h"

#include <iostream>

// Component kezdet

Component::Component(Queue<Component>* newActiveQueue) : activeQueue(newActiveQueue) {}

void Component::setActiveQueue(Queue<Component>* newActiveQueue)
{
    activeQueue = newActiveQueue;
}

void Component::addToActiveQueue()
{
    if (activeQueue == nullptr) {
        throw NonExistentConnection("A component doesn't have an active queue...\n");
    }

    activeQueue->put(this);
}

void Component::setSimulated()
{
    gotSimulated = true;
}

bool Component::simulated()
{
    return gotSimulated;
}

void Component::resetSimulted()
{
    gotSimulated = false;
}

// Component vége


// InputComponent kezdet

InputComponent::InputComponent(size_t inputCount) : inputPinCount(inputCount)
{
    inputPins = new InputPin[inputPinCount];
    inputNodeIDs = new size_t[inputPinCount];
    for (size_t i = 0; i < inputPinCount; i++) {
        inputPins[i].connenctToComponent(this);
    }
}

void InputComponent::resetForSimulation()
{
    for (size_t i = 0; i < inputPinCount; i++) {
        inputPins[i].resetReady();
    }
}

void InputComponent::activateIfReady()
{
    for (size_t i = 0; i < inputPinCount; i++) {
        if (!inputPins[i].isReady()) {
            return;
        }
    }
    addToActiveQueue();
}

InputPin* InputComponent::getInputPinByIndex(size_t idx) const
{
    if (idx >= inputPinCount)
        throw std::out_of_range("Indexed out of inputPin array range...\n");

    return inputPins + idx;
}

void InputComponent::setInputNodeID(size_t at, size_t ID)
{
    if (at >= inputPinCount) {
        throw std::out_of_range("Indexed out of inputNodeID array range...\n");
    }

    inputNodeIDs[at] = ID;
}

bool InputComponent::isConnectedToNodeOnInput(size_t ID)
{
    for (size_t i = 0; i < inputPinCount; i++) {
        if (inputNodeIDs[i] == ID) {
            return true;
        }
    }
    return false;
}

void InputComponent::printConnectedInputNodes(std::ostream& os) const
{
    for (size_t i = 0; i < inputPinCount; i++) {
        os << inputNodeIDs[i];
        if (i != inputPinCount - 1)
            os << " ";
    }
}

InputComponent::~InputComponent()
{
    delete[] inputPins;
    delete[] inputNodeIDs;
}

// InputComponent vége


// OutputComponent kezdet

OutputComponent::OutputComponent(size_t outputCount) : outputPinCount(outputCount)
{
    outputPins = new OutputPin[outputPinCount];
    outputPinIDs = new size_t[outputPinCount];
}

void OutputComponent::connectToInputPin(size_t outputPinIndex, InputComponent* component, size_t inputPinIndex)
{
    if (outputPinIndex >= outputPinCount) {
        throw std::out_of_range("Indexed out of outputPin array range...\n");
    }

    outputPins[outputPinIndex].connectToPin(component->getInputPinByIndex(inputPinIndex));
}

void OutputComponent::sendOutSignals()
{
    for (size_t i = 0; i < outputPinCount; i++) {
        outputPins[i].sendSignal();
    }
}

OutputPin* OutputComponent::getOutputPinByIndex(size_t idx)
{
    if (idx >= outputPinCount) {
        throw std::out_of_range("Indexed out of outputPin array range...\n");
    }

    return outputPins + idx;
}

void OutputComponent::setOutputNodeID(size_t at, size_t ID)
{
    if (at >= outputPinCount) {
        throw std::out_of_range("Indexed out of outputNodeID range...");
    }

    outputPinIDs[at] = ID;
}

bool OutputComponent::isConnectedToNodeOnOutput(size_t ID)
{
    for (size_t i = 0; i < outputPinCount; i++) {
        if (outputPinIDs[i] == ID)
            return true;
    }
    return false;
}

void OutputComponent::printConnectedOutputNodes(std::ostream& os) const
{
    for (size_t i = 0; i < outputPinCount; i++) {
        os << outputPinIDs[i];
        if (i != outputPinCount - 1)
            os << " ";
    }
}

OutputComponent::~OutputComponent()
{
    delete[] outputPins;
    delete[] outputPinIDs;
}

// OutputComponent vége


// IOComponent kezdet

IOComponent::IOComponent(size_t inputCount, size_t outputCount) : InputComponent(inputCount), OutputComponent(outputCount) {}

bool IOComponent::isConnectedToNodes(size_t NodeID1, size_t NodeID2)
{
    return (isConnectedToNodeOnInput(NodeID1) && isConnectedToNodeOnOutput(NodeID2)) || (isConnectedToNodeOnInput(NodeID2) && isConnectedToNodeOnOutput(NodeID1));
}

void IOComponent::printConnectedNodes(std::ostream& os) const
{
    printConnectedInputNodes(os);
    os << " and ";
    printConnectedOutputNodes(os);
}

// IOComponent vége
