#ifndef _LAMP_H
#define _LAMP_H


#include "Component.h"

#include <iostream>
class Lamp : public InPin_Component {
  public:
    Lamp();

    friend std::ostream & operator <<(std::ostream & os, const Lamp & x);

    virtual void executeFunction();

    virtual ~Lamp();

};
#endif
