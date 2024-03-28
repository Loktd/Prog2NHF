
#include "Pin.h"
#include "Component.h"

Pin::Pin(const Signal & signal, const Pin* & connection, const Component* & component) {
}

void Pin::connectWith(const Pin* & other) {
}

void Pin::sendOutSingal() const {
}

void Pin::setSignal(const Signal & newSignal) {
}

void Pin::signalReady() const {
}

Signal::Signal(bool baseValue) {
}

void Signal::setSignal(bool newValue) {
}

bool Signal::getSignal() const {
}

void Signal::flipSignal() {
}

