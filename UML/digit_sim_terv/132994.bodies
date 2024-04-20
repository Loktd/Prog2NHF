class OutPin
!!!160898.cpp!!!	sendSignal() : void
    if (connectedTo == nullptr) {
        throw "ERROR: An output pin doesn't have an associated input pin...";
    }
    connectedTo->setSignal(ownedSignal);
    connectedTo->SignalReady();
