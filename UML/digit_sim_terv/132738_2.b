class InPin
!!!160514.cpp!!!	SignalReady() : void
    if (ofComponent == nullptr) {
        throw "ERROR: An input pin doesn't have an associated component...";
    }
    ofComponent->tickCounter();
