
#include "Lamp.h"

Lamp::Lamp()
    : Component(nullptr), InPin_Component(1)
{
    inPins[0].setSignal(Signal(false));
}

std::ostream& operator<<(std::ostream& os, const Lamp& x)
{
    if (x.getState().getSignal())
        os << "Lamp is glowing, HIGH (1) signal...";
    else
        os << "Lamp is not glowing, LOW (0) signal...";
    return os;
}
