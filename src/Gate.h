#ifndef _GATE_H
#define _GATE_H


#include "Component.h"


class Gate : public IOComponent {
protected:
  /**
   * @brief Végrehajtja a logikai műveletet amit specifikus kapunak kell végeznie.
   *
   */
  virtual void performLogicCalculation() = 0;

public:
  /**
   * @brief Létrehozza a kaput.
   *
   * @param inputCount A bemenetek száma.
   * @param outputCount A kimenetek száma.
   */
  Gate(size_t inputCount, size_t outputCount);

  /**
   * @brief Vérgehajtja a kapu funckióját, azaz a bemeneti jelekből a belső logika alapján előállítja kimeneti jeleket, majd ezeket tovább küldi.
   *
   */
  void executeFunction();

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~Gate();
};


class AND : public Gate {
protected:
  /**
   * @brief AND operációt végrehajtja a bemeneti pin-ek jelein, és beállítja a kimenetet.
   *
   */
  virtual void performLogicCalculation();
public:
  /**
   * @brief Létrehozza az AND kaput.
   *
   * @param inputCount A kapu bemeneteinek száma.
   */
  AND(size_t inputCount);

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~AND();
};


class OR : public Gate {
protected:
  virtual void performLogicCalculation();
public:
  OR(size_t inputCount) : Gate(inputCount, 1) {}
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
  XOR(size_t inputCount) : Gate(inputCount, 1) {}
  virtual ~XOR() {}
};

class NAND : public AND {
  virtual void performLogicCalculation();
public:
  NAND(size_t inputCount) : AND(inputCount) {}
  virtual ~NAND() {}
};

class NOR : public OR {
  virtual void performLogicCalculation();
public:
  NOR(size_t inputCount) : OR(inputCount) {}
  virtual ~NOR() {}
};

class XNOR : public XOR {
  virtual void performLogicCalculation();
public:
  XNOR(size_t inputCount) : XOR(inputCount) {}
  virtual ~XNOR() {}
};
#endif
