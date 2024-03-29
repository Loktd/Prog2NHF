#ifndef _GATE_H
#define _GATE_H


#include "Component.h"

class Gate : public IOPin_Component {
  public:
    Gate();

    virtual void executeFunction() = 0;

    virtual ~Gate();

};
#endif
