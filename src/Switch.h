#ifndef _SWITCH_H
#define _SWITCH_H


#include "Component.h"

class Switch : public IOPin_Component {
  public:
    Switch();

    friend ostream & operator <<(ostream & os, const Switch & x);

    virtual void executeFunction();

    void flipState();

    virtual ~Switch();


  private:
    bool closed;

};
#endif
