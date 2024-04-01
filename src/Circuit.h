#ifndef _CIRCUIT_H
#define _CIRCUIT_H


#include "Queue.h"

class Component;
class Source;
class Switch;
class Lamp;

class Circuit {
  private:
    bool outputValid;

    std::ostream outputStream;

    Queue<Component> componentList;
    Queue<Source> sourceList;
    Queue<Switch> switchList;
    Queue<Lamp> lampList;
    void reset();


  public:
    Circuit(const std::ostream & outStream = std::cout);

    Circuit(const Circuit & source);

    Circuit & operator =(const Circuit & source);

    void setOutputStream(const std::ostream & os);

    void configure(const std::string & fileName);

    void simulate();

    void flipSource(int connectedNode);

    void flipSwitch(int connectedNode1, int connectedNode2);

    void readLampStates() const;

    void readSourceStates() const;

    void readSwitchStates() const;

    ~Circuit();

};
#endif
