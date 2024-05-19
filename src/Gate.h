#ifndef _GATE_H
#define _GATE_H

#include "IOComponent.h"
#include "../test/memtrace.h"

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
  /**
   * @brief OR operációt végrehajtja a bemeneti pin-ek jelein, és beállítja a kimenetet.
   *
   */
  virtual void performLogicCalculation();

public:
  /**
   * @brief Létrehozza az OR kaput.
   *
   * @param inputCount A kapu bemeneteinek száma.
   */
  OR(size_t inputCount);

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~OR();
};


class NOT : public Gate {
protected:
  /**
   * @brief NOT operációt végrehajtja a bemeneti pin-ek jelein, és beállítja a kimenetet.
   *
   */
  virtual void performLogicCalculation();

public:
  /**
   * @brief Létrehozza az NOT kaput.
   *
   */
  NOT();

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~NOT();
};


class XOR : public Gate {
protected:
  /**
   * @brief XOR operációt végrehajtja a bemeneti pin-ek jelein, és beállítja a kimenetet.
   *
   */
  virtual void performLogicCalculation();

public:
  /**
   * @brief Létrehozza az XOR kaput.
   *
   * @param inputCount A kapu bemeneteinek száma.
   */
  XOR(size_t inputCount);

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~XOR();
};


class NAND : public AND {
protected:
  /**
   * @brief NAND operációt végrehajtja a bemeneti pin-ek jelein, és beállítja a kimenetet.
   *
   */
  virtual void performLogicCalculation();

public:
  /**
   * @brief Létrehozza az NAND kaput.
   *
   * @param inputCount A kapu bemeneteinek száma.
   */
  NAND(size_t inputCount);

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~NAND();
};


class NOR : public OR {
protected:
  /**
   * @brief NOR operációt végrehajtja a bemeneti pin-ek jelein, és beállítja a kimenetet.
   *
   */
  virtual void performLogicCalculation();

public:
  /**
   * @brief Létrehozza az NOR kaput.
   *
   * @param inputCount A kapu bemeneteinek száma.
   */
  NOR(size_t inputCount);

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~NOR();
};


class XNOR : public XOR {
protected:
  /**
   * @brief XNOR operációt végrehajtja a bemeneti pin-ek jelein, és beállítja a kimenetet.
   *
   */
  virtual void performLogicCalculation();

public:
  /**
   * @brief Létrehozza az XNOR kaput.
   *
   * @param inputCount A kapu bemeneteinek száma.
   */
  XNOR(size_t inputCount);

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~XNOR();
};

class WIRE : public NOT {
protected:
  /**
   * @brief Vezetéket jelvezetését hajtja végre, nem csinál semmit a jellel.
   *
   */
  virtual void performLogicCalculation();

public:
  /**
   * @brief Létrehozza az vezetéket.
   *
   */
  WIRE();

  /**
   * @brief Virtuális destruktor az öröklés miatt.
   *
   */
  virtual ~WIRE();
};

#endif