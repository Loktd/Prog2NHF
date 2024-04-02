#ifndef _GATE_H
#define _GATE_H


#include "Component.h"

class Gate : public IOPin_Component {
protected:
  virtual void performLogicCalculation() = 0;
public:
  Gate(size_t inCount, size_t outCount) : IOPin_Component(inCount, outCount) {}

  virtual void executeFunction();

  virtual ~Gate() {}
};

class AND : public Gate {
protected:
  virtual void performLogicCalculation();
public:
  AND(size_t inCount) : Gate(inCount, 1) {}
  virtual ~AND() {}
};

class OR : public Gate {
protected:
  virtual void performLogicCalculation();
public:
  OR(size_t inCount) : Gate(inCount, 1) {}
  virtual ~OR() {}
};

class NOT : public Gate {
  virtual void performLogicCalculation();
public:
  NOT() : Gate(1, 1) {}
  virtual ~NOT() {}
};

class XOR : public Gate {
protected:
  virtual void performLogicCalculation();
public:
  XOR(size_t inCount) : Gate(inCount, 1) {}
  virtual ~XOR() {}
};

class NAND : public AND {
  virtual void performLogicCalculation();
public:
  NAND(size_t inCount) : AND(inCount) {}
  virtual ~NAND() {}
};

class NOR : public OR {
  virtual void performLogicCalculation();
public:
  NOR(size_t inCount) : OR(inCount) {}
  virtual ~NOR() {}
};

class XNOR : public XOR {
  virtual void performLogicCalculation();
public:
  XNOR(size_t inCount) : XOR(inCount) {}
  virtual ~XNOR() {}
};
#endif
