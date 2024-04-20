class XOR
!!!138498.cpp!!!	performLogicCalculation() : void
    Signal result(false);
    for (size_t i = 0; i < inPinCount; i++) {
        if (inPins[i].getSignal() == Signal(true)) {
            result.flipSignal();
        }
    }
    outPins[0].setSignal(result);
