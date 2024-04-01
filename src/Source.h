#ifndef _SOURCE_H
#define _SOURCE_H


#include "Component.h"

#include <iostream>
class Source : public OutPin_Component {
  public:
    Source();

    friend std::ostream & operator <<(std::ostream & os, const Source & x);

    virtual void executeFunction();

    void flipSignal();

    virtual ~Source();

};
#endif
