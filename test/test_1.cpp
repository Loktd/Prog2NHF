#include <iostream>

#include "../src/Pin.h"
#include "../src/Component.h"
#include "../src/Source.h"
#include "../src/Lamp.h"
#include "../src/Node.h"
#include "../src/Switch.h"

int main() {
    Queue<Component>* active = new Queue<Component>;

    Source* src = new Source;
    src->setActiveQueue(active);

    Lamp* lamp = new Lamp;
    lamp->setActiveQueue(active);
    Lamp* lamp2 = new Lamp;
    lamp2->setActiveQueue(active);

    Node* node = new Node(2);
    node->setActiveQueue(active);

    Switch* sw = new Switch;
    sw->setActiveQueue(active);

    src->connectTo(0, node, 0);
    node->connectTo(0, lamp, 0);
    node->connectTo(1, sw, 0);
    sw->connectTo(0, lamp2, 0);

    src->setOutput(Signal(true));
    sw->flipState();
    sw->flipState();

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
}