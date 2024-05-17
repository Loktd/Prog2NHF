#include "IOComponent.h"

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