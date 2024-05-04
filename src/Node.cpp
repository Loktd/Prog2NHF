
#include "Node.h"

#include <string>

InputPin* Node::getInPin()
{
    return inputPins;
}

size_t Node::getID() const
{
    return ID;
}

void Node::addOutPin(InputPin* endPoint)
{
    OutputPin* nextOut = new OutputPin();
    nextOut->connectToPin(endPoint);
    outPins.put(nextOut);
}

void Node::executeFunction() {
    Queue<OutputPin> copy(outPins);
    while (!copy.isEmpty()) {
        OutputPin* current = copy.get();
        current->setSignal(inputPins[0].getSignal());
        current->sendSignal();
    }
}
