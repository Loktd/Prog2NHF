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
    Node* node = new Node(1);
    node->setActiveQueue(active);
    Lamp* lamp = new Lamp;
    lamp->setActiveQueue(active);
}