
#include "Switch.h"

void Switch::executeFunction() {
    if (closed)
        outputPins[0].setSignal(inputPins[0].getSignal());
    else
        outputPins[0].setSignal(Signal(false));
    sendOutSignals();
}

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
