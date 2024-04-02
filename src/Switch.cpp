
#include "Switch.h"

void Switch::executeFunction() {
    if (closed)
        outPins[0].setSignal(inPins[0].getSignal());
    else
        outPins[0].setSignal(Signal(false));
    sendOutSignals();
}

std::ostream& operator<<(std::ostream& os, const Switch& x)
{
    if (x.getState())
        os << "Switch is closed...";
    else
        os << "Switch is open...";
    return os;
}
