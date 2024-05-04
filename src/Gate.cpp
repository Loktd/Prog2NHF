#include "Gate.h"

// Gate kezdet

Gate::Gate(size_t inputCount, size_t outputCount) : IOComponent(inputCount, outputCount) {}

void Gate::executeFunction()
{
    performLogicCalculation();
    sendOutSignals();
}

Gate::~Gate() {}

// Gate vége


// AND kezdet

void AND::performLogicCalculation()
{
    Signal result(true);
    for (size_t i = 0; i < inputPinCount; i++) {
        if (inputPins[i].getSignal() == Signal(false)) {
            result.setValue(false);
            break;
        }
    }
    outputPins[0].setSignal(result);
}

AND::AND(size_t inputCount) : Gate(inputCount, 1) {}

AND::~AND() {}

// AND vége

void OR::performLogicCalculation()
{
    Signal result(false);
    for (size_t i = 0; i < inputPinCount; i++) {
        if (inputPins[i].getSignal() == Signal(true)) {
            result.setValue(true);
            break;
        }
    }
    outputPins[0].setSignal(result);
}


void NOT::performLogicCalculation()
{
    Signal result = inputPins[0].getSignal();
    result.flip();
    outputPins[0].setSignal(result);
}

void XOR::performLogicCalculation()
{
    Signal result(false);
    for (size_t i = 0; i < inputPinCount; i++) {
        if (inputPins[i].getSignal() == Signal(true)) {
            result.flip();
        }
    }
    outputPins[0].setSignal(result);
}

void NAND::performLogicCalculation()
{
    AND::performLogicCalculation();
    outputPins[0].flipSignal();
}

void NOR::performLogicCalculation()
{
    OR::performLogicCalculation();
    outputPins[0].flipSignal();
}

void XNOR::performLogicCalculation()
{
    XOR::performLogicCalculation();
    outputPins[0].flipSignal();
}
