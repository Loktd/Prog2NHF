#ifndef _NODE_H
#define _NODE_H

#include "Component.h"

#include <iostream>

class Node : public InputComponent {
  size_t ID;
  Queue<OutputPin> outPins;
public:
  Node(size_t nodeID) : InputComponent(1), ID(nodeID), outPins(true) {}

  InputPin* getInPin();
  size_t getID() const;
  void addOutPin(InputPin* endPoint);

  virtual void executeFunction();

  virtual ~Node() {}
};
#endif
