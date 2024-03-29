#ifndef _SOURCE_H
#define _SOURCE_H


#include "Component.h"
#include "Pin.h"

#include <iostream>
class Source : public OutPin_Component {
  private:
    Signal sentSignal;

  public:
    Source();

    friend std::ostream & operator <<(std::ostream & os, const Source & x);

    virtual void executeFunction();

    void flipSignal();

    virtual ~Source();

};
#endif
