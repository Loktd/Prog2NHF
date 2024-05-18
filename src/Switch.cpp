#include "Switch.h"


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
