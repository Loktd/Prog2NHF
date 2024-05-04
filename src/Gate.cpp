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


// OR kezdet

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

OR::OR(size_t inputCount) : Gate(inputCount, 1) {}

OR::~OR() {}

// OR vége


// NOT kezdet

void NOT::performLogicCalculation()
{
    Signal result = inputPins[0].getSignal();
    result.flip();
    outputPins[0].setSignal(result);
}

NOT::NOT() : Gate(1, 1) {}

NOT::~NOT() {}

// NOT vége


// XOR kezdet

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

XOR::XOR(size_t inputCount) : Gate(inputCount, 1) {}

XOR::~XOR() {}

// XOR vége


// NAND kezdet

void NAND::performLogicCalculation()
{
    AND::performLogicCalculation();
    outputPins[0].flipSignal();
}

NAND::NAND(size_t inputCount) : AND(inputCount) {}

NAND::~NAND() {}

// NAND vége


// NOR kezdet

void NOR::performLogicCalculation()
{
    OR::performLogicCalculation();
    outputPins[0].flipSignal();
}

NOR::NOR(size_t inputCount) : OR(inputCount) {}

NOR::~NOR() {}

// NOR vége


// XNOR kezdet

void XNOR::performLogicCalculation()
{
    XOR::performLogicCalculation();
    outputPins[0].flipSignal();
}

XNOR::XNOR(size_t inputCount) : XOR(inputCount) {}

XNOR::~XNOR() {}

// XNOR vége