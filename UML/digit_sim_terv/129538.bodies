class OutPin_Component
!!!135042.cpp!!!	OutPin_Component(in outCount : size_t)
    outPinCount = outCount;
    outPins = new OutPin[outPinCount];
    outPinIDs = new size_t[outPinCount];
!!!135170.cpp!!!	connectTo(in outPinIndex : size_t, inout component : InPin_Component, in inPinIndex : size_t) : void
    outPins[outPinIndex].connectToPin(component->getInPinsBaseAdress() + inPinIndex);
!!!135298.cpp!!!	sendOutSignals() : void
    for (size_t i = 0; i < outPinCount; i++) {
        outPins[i].sendSignal();
    }
!!!135554.cpp!!!	setOutNodeID(in at : size_t, in id : size_t) : void
    if (at >= outPinCount) {
        throw std::string("Indexed out of outNodeID range...");
    }
    outPinIDs[at] = id;
!!!135682.cpp!!!	connectedToNodeOut(in id : size_t) : bool
    for (size_t i = 0; i < outPinCount; i++) {
        if (outPinIDs[i] == id)
            return true;
    }
    return false;
!!!135810.cpp!!!	printOutConnectedNodes(inout os : std::ostream) : void
    for (size_t i = 0; i < outPinCount; i++) {
        os << outPinIDs[i];
        if (i != outPinCount - 1)
            os << " ";
    }
!!!136066.cpp!!!	~OutPin_Component()
    delete[] outPins;
    delete[] outPinIDs;
