#ifndef _LAMP_H
#define _LAMP_H


#include "Component.h"

class Lamp : public InPin_Component {
  public:
    Lamp();

    friend ostream & operator <<(ostream & os, const Lamp & x);

    virtual void executeFunction();

    virtual ~Lamp();

};
#endif
