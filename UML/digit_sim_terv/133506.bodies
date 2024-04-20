class AND
!!!155522.cpp!!!	performLogicCalculation() : void
    Signal result(true);
    for (size_t i = 0; i < inPinCount; i++) {
        if (inPins[i].getSignal() == Signal(false)) {
            result.setValue(false);
            break;
        }
    }
    outPins[0].setSignal(result);
