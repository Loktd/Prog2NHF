#include "Pin.h"


Pin::Pin(Signal baseSignal) : ownedSignal(baseSignal) {}

void Pin::setSignal(const Signal& newSignal)
{
    ownedSignal = newSignal;
}

Signal Pin::getSignal() const
{
    return ownedSignal;
}

void Pin::flipSignal()
{
    ownedSignal.flip();
}

Pin::~Pin() {}