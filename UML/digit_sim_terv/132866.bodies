class OutPin_Component
!!!153218.cpp!!!	OutPin_Component(in outCount : size_t)
    outPinCount = outCount;
    outPins = new OutPin[outPinCount];
    outPinIDs = new size_t[outPinCount];
!!!153346.cpp!!!	connectTo(in outPinIndex : size_t, inout component : InPin_Component, in inPinIndex : size_t) : void
    outPins[outPinIndex].connectToPin(component->getInPinsBaseAdress() + inPinIndex);
!!!153474.cpp!!!	sendOutSignals() : void
    for (size_t i = 0; i < outPinCount; i++) {
        outPins[i].sendSignal();
    }
!!!153730.cpp!!!	setOutNodeID(in at : size_t, in id : size_t) : void
    if (at >= outPinCount) {
        throw std::string("Indexed out of outNodeID range...");
    }
    outPinIDs[at] = id;
!!!153858.cpp!!!	connectedToNodeOut(in id : size_t) : bool
    for (size_t i = 0; i < outPinCount; i++) {
        if (outPinIDs[i] == id)
            return true;
    }
    return false;
!!!153986.cpp!!!	printOutConnectedNodes(inout os : std::ostream) : void
    for (size_t i = 0; i < outPinCount; i++) {
        os << outPinIDs[i];
        if (i != outPinCount - 1)
            os << " ";
    }
!!!154242.cpp!!!	~OutPin_Component()
    delete[] outPins;
    delete[] outPinIDs;
