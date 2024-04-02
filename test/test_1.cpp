#include <iostream>

#include "../src/Pin.h"
#include "../src/Component.h"
#include "../src/Source.h"
#include "../src/Lamp.h"
#include "../src/Node.h"

int main() {
    Queue<Component>* active = new Queue<Component>;

    Source* src = new Source;
    src->setActiveQueue(active);

    Lamp* lamp = new Lamp;
    lamp->setActiveQueue(active);

    src->connectTo(0, lamp, 0);
    src->setOutput(Signal(false));

    src->addToActiveQueue();

    try {
        while (!active->isEmpty()) {
            Component* current = active->get();
            current->executeFunction();
        }
    }
    catch (const char* str) {
        std::cout << str << std::endl;
    }

    std::cout << *lamp;
}