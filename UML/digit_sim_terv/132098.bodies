class Node
!!!158850.cpp!!!	getInPin() : InPin
    return inPins;
!!!158978.cpp!!!	getID() : size_t
    return ID;
!!!159106.cpp!!!	addOutPin(inout endPoint : InPin) : void
    OutPin* nextOut = new OutPin();
    nextOut->connectToPin(endPoint);
    outPins.put(nextOut);
!!!159234.cpp!!!	executeFunction() : void
    Queue<OutPin> copy(outPins);
    while (!copy.isEmpty()) {
        OutPin* current = copy.get();
        current->setSignal(inPins[0].getSignal());
        current->sendSignal();
    }
