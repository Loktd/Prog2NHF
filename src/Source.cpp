
#include "Source.h"

Source::Source()
    : Component(nullptr), OutPin_Component(1)
{
    outPins[0].setSignal(Signal(false));
}


std::ostream& operator<<(std::ostream& os, const Source& x) {
    if (x.getOutput().getSignal())
        os << "Source is outputting HIGH (1) signal...";
    else
        os << "Source is outputting LOW (0) signal...";
    return os;
}