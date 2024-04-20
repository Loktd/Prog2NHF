class Node
!!!140674.cpp!!!	getInPin() : InPin
    return inPins;
!!!140802.cpp!!!	getID() : size_t
    return ID;
!!!140930.cpp!!!	addOutPin(inout endPoint : InPin) : void
    OutPin* nextOut = new OutPin();
    nextOut->connectToPin(endPoint);
    outPins.put(nextOut);
!!!141058.cpp!!!	executeFunction() : void
    Queue<OutPin> copy(outPins);
    while (!copy.isEmpty()) {
        OutPin* current = copy.get();
        current->setSignal(inPins[0].getSignal());
        current->sendSignal();
    }
