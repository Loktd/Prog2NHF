
#include "Source.h"

Source::Source()
    : Component(nullptr), OutPin_Component(1)
{
    outPins[0].setSignal(Signal(false));
}

std::ostream& operator<<(std::ostream& os, const Source& x) {
    os << "Source connected to node ";
    x.printOutConnectedNodes(os);
    if (x.getOutput().getSignal())
        os << ": outputting HIGH (1) signal...";
    else
        os << ": outputting LOW (0) signal...";
    return os;
}