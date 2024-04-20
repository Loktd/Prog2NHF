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
#include <sstream>
#include <string>

class Circuit {
  std::ostream* errorStream;
  std::string inputFileName;
  std::ifstream inputfile;

  Queue<Component> componentList;
  Queue<InputComponent> incomponents;
  Queue<Source> sourceList;
  Queue<Switch> switchList;
  Queue<Lamp> lampList;
  Queue<Component> activeList;
  Queue<Node> nodeList;

  bool configured;
  bool simulated;

  void reset();
  void configure();

  void build();
  enum ComponentType {
    INVALID = 0, SOURCE = 1, LAMP = 2, SWITCH = 3, And = 4, Or = 5, Not = 6, Xor = 7, Nand = 8, Nor = 9, Xnor = 10
  };
  struct ContentInfo {
    size_t lineCount;
    std::string line;
    size_t idx;
    ComponentType type;
    ContentInfo() : lineCount(0), line(""), idx(0), type(INVALID) {}
  };
  void buildLine(ContentInfo& info);
  void checkLineType(ContentInfo& info);
  void buildComponent(ContentInfo& info);
  void getNodeNumbers(ContentInfo& info, Queue<int>& nodeNumbers);
  void checkNodeCount(ContentInfo& info, size_t count);
  void createBasedOnType(ContentInfo& info, size_t count, Queue<int>& nodeNumbers);

  template<typename T>
  void create(size_t count, Queue<int>& nodeNumbers);

  template<typename T>
  void create(Queue<int>& nodeNumbers);

  void connectInPinWithNode(InputPin* pin, size_t id, size_t idx);
  void connectOutPinWithNode(OutputComponent* component, OutputPin* pin, size_t id, size_t idx);

public:
  Circuit();
  Circuit(const Circuit& source);
  Circuit& operator=(const Circuit& source);

  void setErrorStream(std::ostream* os);

  void setSourceFile(const std::string& fileName);
  const std::string& getSourceFileName() const;

  void simulate(std::ostream& os);

  void setSource(size_t connectedNode, Signal newSignal);
  void setSwitch(size_t connectedNode1, size_t connectedNode2, bool closed);

  void printAllSourceStates(std::ostream& os) const;
  void printAllSwitchStates(std::ostream& os) const;
  void printAllLampStates(std::ostream& os) const;

  ~Circuit();
};

std::ostream& operator<<(std::ostream& os, const Circuit& circuit);
void printSeparatorLine(std::ostream& os, char c, int times);

template<typename T>
void Circuit::create(size_t count, Queue<int>& nodeNumbers) {
  T* created = new T(count - 1);
  ((Component*)created)->setActiveQueue(&activeList);
  Queue<int> copy(nodeNumbers);
  for (size_t i = 0; i < count - 1; i++) {
    connectInPinWithNode(((InputComponent*)created)->getInPinsBaseAdress() + i, *(copy.get()), i);
  }
  connectOutPinWithNode(created, ((OutputComponent*)created)->getOutPinBaseAdress(), *(copy.get()), 0);
  componentList.put(created);
  incomponents.put(created);
}

#endif