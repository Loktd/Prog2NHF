
#include "Gate.h"

void Gate::executeFunction()
{
    performLogicCalculation();
    sendOutSignals();
}

void AND::performLogicCalculation()
{
    Signal result(true);
    for (size_t i = 0; i < inPinCount; i++) {
        if (inPins[i].getSignal() == Signal(false)) {
            result.setValue(false);
            break;
        }
    }
    outPins[0].setSignal(result);
}

void OR::performLogicCalculation()
{
    Signal result(false);
    for (size_t i = 0; i < inPinCount; i++) {
        if (inPins[i].getSignal() == Signal(true)) {
            result.setValue(true);
            break;
        }
    }
    outPins[0].setSignal(result);
}


void NOT::performLogicCalculation()
{
    Signal result = inPins[0].getSignal();
    result.flip();
    outPins[0].setSignal(result);
}

void XOR::performLogicCalculation()
{
    Signal result(false);
    for (size_t i = 0; i < inPinCount; i++) {
        if (inPins[i].getSignal() == Signal(true)) {
            result.flip();
        }
    }
    outPins[0].setSignal(result);
}

void NAND::performLogicCalculation()
{
    AND::performLogicCalculation();
    outPins[0].flipSignal();
}

void NOR::performLogicCalculation()
{
    OR::performLogicCalculation();
    outPins[0].flipSignal();
}

void XNOR::performLogicCalculation()
{
    XOR::performLogicCalculation();
    outPins[0].flipSignal();
}
