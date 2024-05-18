#include "Node.h"


Node::Node(size_t nodeID) : InputComponent(1), ID(nodeID), outputPins(true) {}

InputPin* Node::getInPin()
{
    return inputPins;
}

size_t Node::getID() const
{
    return ID;
}

void Node::addOutputPin(InputPin* endPoint)
{
    OutputPin* nextOut = new OutputPin();
    nextOut->connectToPin(endPoint);
    outputPins.put(nextOut);
}

void Node::executeFunction() {
    for (Queue<OutputPin>::iterator it = outputPins.begin(); it != outputPins.end(); it++) {
        OutputPin* current = *it;
        current->setSignal(inputPins[0].getSignal());
        current->sendSignal();
    }
}

Node::~Node() {}