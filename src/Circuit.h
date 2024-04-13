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
  Queue<Source> sourceList;
  Queue<Switch> switchList;
  Queue<Lamp> lampList;
  Queue<Component> activeList;
  Queue<Node> nodeList;

  void reset();
  void configure();

  void build();
  enum ComponentType {
    INVALID = 0, SOURCE = 1, LAMP = 2, SWITCH = 3, AND = 4, OR = 5, NOT = 6, XOR = 7, NAND = 8, NOR = 9, XNOR = 10
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
  void checkNodeCount(ContentInfo& info, Queue<int>& nodeNumbers);

public:
  Circuit();
  Circuit(const Circuit& source);
  Circuit& operator=(const Circuit& source);

  static void setErrorStream(std::ostream* os);

  void setSourceFile(const std::string& fileName);
  const std::string& getSourceFileName() const;

  void simulate(std::ostream& os);

  void setSource(int connectedNode, Signal newSignal);
  void setAllSources(int* connectedNodes, Signal* newSignals);
  void flipSource(int connectedNode);
  void flipAllSources();
  Signal getSourceSignal(int connectedNode) const;
  void printSourceState(std::ostream& os) const;
  void printAllSourceStates(std::ostream& os) const;

  void setSwitch(int connectedNode1, int connectedNode2, bool closed);
  void setAllSwitches(int* connectedNodes1, int* connectedNodes2, bool* closedStates);
  void flipSwitch(int connectedNode1, int connectedNode2);
  void flipAllSwitches();
  bool isSwitchClosed(int connectedNode1, int connectedNode2);
  void printSwitchState(int connectedNode1, int connectedNode2, std::ostream& os) const;
  void printAllSwitchStates(std::ostream& os) const;

  Signal getLampSignal() const;
  bool isLampGlowing() const;
  void printLampState(int connectedNode, std::ostream& os);
  void printAllLampStates(std::ostream& os) const;

  ~Circuit();
};

std::ostream& operator<<(std::ostream& os, const Circuit& circuit);
void printSeparatorLine(std::ostream& os, char c, int times);

#endif