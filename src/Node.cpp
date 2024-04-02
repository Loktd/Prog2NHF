
#include "Node.h"

void Node::executeFunction() {
    for (size_t i = 0; i < outPinCount; i++) {
        outPins[i].setSignal(inPins[0].getSignal());
    }
    sendOutSignals();
}
