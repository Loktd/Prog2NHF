
#include "Node.h"

InPin* Node::getInPin()
{
    return inPins;
}

size_t Node::getID() const
{
    return ID;
}

void Node::addOutPin(InPin* endPoint)
{
    OutPin* nextOut = new OutPin();
    nextOut->connectToPin(endPoint);
    outPins.put(nextOut);
}

void Node::executeFunction() {
    Queue<OutPin> copy(outPins);
    while (!copy.isEmpty()) {
        OutPin* current = copy.get();
        current->setSignal(inPins[0].getSignal());
        current->sendSignal();
    }
}
