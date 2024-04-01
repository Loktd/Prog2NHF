#include <iostream>

#include "../src/Component.h"

int main() {
    Queue<Signal> fifo;
    fifo.put(new Signal(true));
    delete fifo.get();
}