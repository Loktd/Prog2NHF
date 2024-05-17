#include "InputPin.h"

InputPin::InputPin(Signal baseSignal) : Pin(baseSignal), component(nullptr), ready(false) {}

void InputPin::connenctToComponent(InputComponent* connected)
{
    component = connected;
}

InputComponent* InputPin::getComponent() const
{
    return component;
}

bool InputPin::isReady()
{
    return ready;
}

void InputPin::setReady()
{
    if (component == nullptr) {
        throw NonExistentConnection("An InputPin doesn't have a connected component while sending a message...");
    }

    ready = true;
    component->activateIfReady();
}

void InputPin::resetReady()
{
    ready = false;
}

InputPin::~InputPin() {}