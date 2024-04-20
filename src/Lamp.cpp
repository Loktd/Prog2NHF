
#include "Lamp.h"

Lamp::Lamp()
    : Component(nullptr), InputComponent(1)
{
    inPins[0].setSignal(Signal(false));
}

std::ostream& operator<<(std::ostream& os, const Lamp& x)
{
    os << "Lamp connected to node ";
    x.printInConnectedNodes(os);
    if (x.getState().getValue())
        os << ": glowing, HIGH (1) signal...";
    else
        os << ": not glowing, LOW (0) signal...";
    return os;
}
