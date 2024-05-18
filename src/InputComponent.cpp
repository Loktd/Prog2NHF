#include "InputComponent.h"


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
        throw std::out_of_range("Indexed out of inputPin array range...");

    return inputPins + idx;
}

void InputComponent::setInputNodeID(size_t at, size_t ID)
{
    if (at >= inputPinCount) {
        throw std::out_of_range("Indexed out of inputNodeID array range...");
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
