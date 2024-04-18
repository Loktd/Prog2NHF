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
  static std::ostream* errorStream;

  bool configured;
  bool simulated;

  std::string inputFileName;
  std::ifstream inputfile;

  Queue<Component> componentList;
  Queue<InPin_Component> incomponents;
  Queue<Source> sourceList;
  Queue<Switch> switchList;
  Queue<Lamp> lampList;
  Queue<Component> activeList;
  Queue<Node> nodeList;

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

  void connectInPinWithNode(InPin* pin, size_t id, size_t idx);
  void connectOutPinWithNode(OutPin_Component* component, OutPin* pin, size_t id, size_t idx);

public:
  Circuit();
  Circuit(const Circuit& source);
  Circuit& operator=(const Circuit& source);

  static void setErrorStream(std::ostream* os);

  void setSourceFile(const std::string& fileName);
  const std::string& getSourceFileName() const;

  void simulate(std::ostream& os);

  void setSource(size_t connectedNode, Signal newSignal);
  void setAllSources(int* connectedNodes, Signal* newSignals);
  void flipSource(size_t connectedNode);
  void flipAllSources();
  Signal getSourceSignal(size_t connectedNode) const;
  void printSourceState(std::ostream& os) const;
  void printAllSourceStates(std::ostream& os) const;

  void setSwitch(size_t connectedNode1, size_t connectedNode2, bool closed);
  void setAllSwitches(size_t* connectedNodes1, size_t* connectedNodes2, bool closedStates[]);
  void flipSwitch(size_t connectedNode1, size_t connectedNode2);
  void flipAllSwitches();
  bool isSwitchClosed(size_t connectedNode1, size_t connectedNode2);
  void printSwitchState(size_t connectedNode1, size_t connectedNode2, std::ostream& os) const;
  void printAllSwitchStates(std::ostream& os) const;

  Signal getLampSignal(int connectedNode) const;
  bool isLampGlowing(int connectedNode) const;
  void printLampState(int connectedNode, std::ostream& os);
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
    connectInPinWithNode(((InPin_Component*)created)->getInPinsBaseAdress() + i, *(copy.get()), i);
  }
  connectOutPinWithNode(created, ((OutPin_Component*)created)->getOutPinBaseAdress(), *(copy.get()), 0);
  componentList.put(created);
  incomponents.put(created);
}

#endif