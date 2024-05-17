#include "Component.h"

Component::Component(Queue<Component>* newActiveQueue) : activeQueue(newActiveQueue) {}

void Component::setActiveQueue(Queue<Component>* newActiveQueue)
{
    activeQueue = newActiveQueue;
}

void Component::addToActiveQueue()
{
    if (activeQueue == nullptr) {
        throw NonExistentConnection("A component doesn't have an active queue...\n");
    }

    activeQueue->put(this);
}

void Component::setSimulated()
{
    gotSimulated = true;
}

bool Component::simulated()
{
    return gotSimulated;
}

void Component::resetSimulted()
{
    gotSimulated = false;
}

Component::~Component() {}
