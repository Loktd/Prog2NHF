#ifndef _SWITCH_H
#define _SWITCH_H


#include "Component.h"

#include <iostream>
class Switch : public IOPin_Component {
  public:
    Switch();

    friend std::ostream & operator <<(std::ostream & os, const Switch & x);

    virtual void executeFunction();

    void flipState();

    virtual ~Switch();


  private:
    bool closed;

};
#endif
