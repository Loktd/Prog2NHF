#ifndef _NODE_H
#define _NODE_H


#include "Component.h"

#include <iostream>
class Node : public IOPin_Component {
  public:
    Node();

    virtual void executeFunction();

    virtual ~Node();

};
#endif
