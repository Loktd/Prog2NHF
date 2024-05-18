#include "Lamp.h"

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
