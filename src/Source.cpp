
#include "Source.h"

Source::Source()
    : Component(nullptr), OutputComponent(1)
{
    outputPins[0].setSignal(Signal(false));
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