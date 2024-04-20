class NOT
!!!156290.cpp!!!	performLogicCalculation() : void
    Signal result = inPins[0].getSignal();
    result.flipSignal();
    outPins[0].setSignal(result);
!!!156290.cpp!!!	performLogicCalculation() : void
    Signal result = inPins[0].getSignal();
    result.flip();
    outPins[0].setSignal(result);
