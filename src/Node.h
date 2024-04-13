#ifndef _NODE_H
#define _NODE_H

#include "Component.h"

#include <iostream>

class Node : public IOPin_Component {
public:
  Node(size_t outCount) : IOPin_Component(1, outCount) {}

  virtual void executeFunction();

  virtual ~Node() {}
};

class Wire : private Node {
public:
  Wire() : Node(1) {}

  virtual void executeFunction() { Node::executeFunction(); }

  virtual ~Wire() {}
};
#endif
