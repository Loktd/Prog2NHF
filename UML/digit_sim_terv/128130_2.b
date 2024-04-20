class Component
!!!133378.cpp!!!	addToActiveQueue() : void
    if (activeQueue == nullptr)
        throw "This component doesn't have an active queue...";
    activeQueue->put(this);
