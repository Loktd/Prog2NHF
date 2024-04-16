#ifndef _NODE_H
#define _NODE_H

#include "Component.h"

#include <iostream>

class Node : public InPin_Component {
  size_t ID;
  Queue<OutPin> outPins;
public:
  Node(size_t nodeID) : InPin_Component(1), ID(nodeID), outPins(true) {}

  InPin* getInPin();
  size_t getID() const;
  void addOutPin(InPin* endPoint);

  virtual void executeFunction();

  virtual ~Node() {}
};
#endif
