#include <iostream>

#include "../src/Pin.h"
#include "../src/Component.h"
#include "../src/Source.h"
#include "../src/Lamp.h"

int main() {
    Queue<Component>* active = new Queue<Component>;
    Source* src = new Source;
    src->setActiveQueue(active);
    Lamp* lamp = new Lamp;
    lamp->setActiveQueue(active);
}