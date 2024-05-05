#include "Peripherals.h"

// Source kezdet

Source::Source() : Component(nullptr), OutputComponent(1)
{
    outputPins[0].setSignal(Signal(false));
}

void Source::executeFunction()
{
    sendOutSignals();
}

void Source::setOutput(const Signal& signal)
{
    outputPins[0].setSignal(signal);
}

Signal Source::getOutput() const
{
    return outputPins[0].getSignal();
}

void Source::flipOutput()
{
    outputPins[0].flipSignal();
}

std::ostream& operator<<(std::ostream& os, const Source& x) {
    os << "Source connected to node ";
    x.printConnectedOutputNodes(os);
    if (x.getOutput().getValue())
        os << ": outputting HIGH (1) signal...";
    else
        os << ": outputting LOW (0) signal...";
    return os;
}

// Source vége


// Switch kezdet

Switch::Switch() : IOComponent(1, 1), closed(false) {}

void Switch::executeFunction() {
    if (closed)
        outputPins[0].setSignal(inputPins[0].getSignal());
    else
        outputPins[0].setSignal(Signal(false));
    sendOutSignals();
}

bool Switch::getState() const
{
    return closed;
}

void Switch::setState(bool newState)
{
    closed = newState;
}

void Switch::flipState()
{
    closed = !closed;
}

Switch::~Switch() {}

std::ostream& operator<<(std::ostream& os, const Switch& x)
{
    os << "Switch connected to nodes ";
    x.printConnectedNodes(os);
    if (x.getState())
        os << " is closed...";
    else
        os << " is open...";
    return os;
}

// Switch vége


// Lamp kezdet

Lamp::Lamp() : Component(nullptr), InputComponent(1)
{
    inputPins[0].setSignal(Signal(false));
}

Signal Lamp::getState() const
{
    return inputPins[0].getSignal();
}

void Lamp::executeFunction() {}

Lamp::~Lamp() {}

std::ostream& operator<<(std::ostream& os, const Lamp& x)
{
    os << "Lamp connected to node ";
    x.printConnectedInputNodes(os);
    if (x.getState().getValue())
        os << ": glowing, HIGH (1) signal...";
    else
        os << ": not glowing, LOW (0) signal...";
    return os;
}

// Lamp vége


// Node kezdet

Node::Node(size_t nodeID) : InputComponent(1), ID(nodeID), outputPins(true) {}

InputPin* Node::getInPin()
{
    return inputPins;
}

size_t Node::getID() const
{
    return ID;
}

void Node::addOutputPin(InputPin* endPoint)
{
    OutputPin* nextOut = new OutputPin();
    nextOut->connectToPin(endPoint);
    outputPins.put(nextOut);
}

void Node::executeFunction() {
    for (Queue<OutputPin>::iterator it = outputPins.begin(); it != outputPins.end(); it++) {
        OutputPin* current = *it;
        current->setSignal(inputPins[0].getSignal());
        current->sendSignal();
    }
}

Node::~Node() {}

// Node vége