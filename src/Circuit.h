#ifndef _CIRCUIT_H
#define _CIRCUIT_H

#include "Component.h"
#include "Gate.h"
#include "Lamp.h"
#include "Node.h"
#include "Pin.h"
#include "Queue.h"
#include "Signal.h"
#include "Source.h"
#include "Switch.h"

#include <iostream>
#include <fstream>
#include <cstring>

class Circuit {
  static std::ostream* errorStream;

  bool configured;
  bool outputValid;

  std::string inputFileName;
  std::ifstream inputfile;

  Queue<Component>* componentList;
  Queue<Source>* sourceList;
  Queue<Switch>* switchList;
  Queue<Lamp>* lampList;

  Queue<Component>* activeList;

  void nullifyPointers();
  void allocateMemory();
  void deleteMemory();

  void checkSyntax();
  void configure();

public:
  Circuit();
  Circuit(const Circuit& source);
  Circuit& operator=(const Circuit& source);

  void setInputFile(const std::string& fileName);
  const std::string& getInputFileName() const;

  static void setErrorStream(std::ostream* os);

  void simulate();

  void flipSource(int connectedNode);
  void flipSwitch(int connectedNode1, int connectedNode2);

  void printLampStates(std::ostream& os) const;
  void printSourceStates(std::ostream& os) const;
  void printSwitchStates(std::ostream& os) const;

  ~Circuit();
};

std::ostream& operator<<(std::ostream& os, const Circuit& circuit);
void printSeparatorLine(std::ostream& os, char c, int times);
#endif
