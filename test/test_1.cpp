#include <iostream>

#include "memtrace.h"

#include "../src/Pin.h"
#include "../src/Component.h"
#include "../src/Source.h"
#include "../src/Lamp.h"
#include "../src/Node.h"
#include "../src/Switch.h"
#include "../src/Gate.h"

int main() {
    Queue<Component>* components = new Queue<Component>(true);
    Queue<Component>* active = new Queue<Component>(false);

    Source* src = new Source;
    components->put(src);
    src->setActiveQueue(active);

    Lamp* lamp = new Lamp;
    components->put(lamp);
    lamp->setActiveQueue(active);

    Lamp* lamp2 = new Lamp;
    components->put(lamp2);
    lamp2->setActiveQueue(active);

    Node* node = new Node(3);
    components->put(node);
    node->setActiveQueue(active);

    Switch* sw = new Switch;
    components->put(sw);
    sw->setActiveQueue(active);

    NOT* n = new NOT;
    components->put(n);
    n->setActiveQueue(active);

    XNOR* xorgate = new XNOR(2);
    components->put(xorgate);
    xorgate->setActiveQueue(active);

    src->connectTo(0, node, 0);
    node->connectTo(0, xorgate, 0);
    node->connectTo(1, n, 0);
    node->connectTo(2, sw, 0);
    sw->connectTo(0, lamp2, 0);
    n->connectTo(0, xorgate, 1);
    xorgate->connectTo(0, lamp, 0);

    src->setOutput(Signal(true));

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

    std::cout << *lamp << std::endl << std::endl;

    std::cout << *sw << std::endl;
    std::cout << *lamp2 << std::endl;

    delete components;
    delete active;
}