#include "Source.h"

Source::Source() : Component(nullptr), OutputComponent(1)
{
    outputPins[0].setSignal(Signal(false));
}

void Source::executeFunction()
{
    sendOutSignals();
}

void Source::setOutput(const Signal& signal)
{
    outputPins[0].setSignal(signal);
}

Signal Source::getOutput() const
{
    return outputPins[0].getSignal();
}

void Source::flipOutput()
{
    outputPins[0].flipSignal();
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