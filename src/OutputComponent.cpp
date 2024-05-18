#include "OutputComponent.h"


OutputComponent::OutputComponent(size_t outputCount) : outputPinCount(outputCount)
{
    outputPins = new OutputPin[outputPinCount];
    outputPinIDs = new size_t[outputPinCount];
}

void OutputComponent::connectToInputPin(size_t outputPinIndex, InputComponent* component, size_t inputPinIndex)
{
    if (outputPinIndex >= outputPinCount) {
        throw std::out_of_range("Indexed out of outputPin array range...");
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
        throw std::out_of_range("Indexed out of outputPin array range...");
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