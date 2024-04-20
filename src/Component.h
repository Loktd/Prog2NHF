#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Pin.h"
#include "Queue.h"

typedef long long unsigned int size_t;

class Component {
protected:
  /**
   * @brief Az aktív sor, amihez kell hozzáadni, ha ki kell értékelni az elemet, azaz végrehajtani a funkcióját.
   */
  Queue<Component>* activeQueue;

public:
  /**
   * @brief Felparaméterezi az aktív sort.
   *
   * @param newActiveQueue A kívánt aktív sor.
   */
  Component(Queue<Component>* newActiveQueue = nullptr) : activeQueue(newActiveQueue) {}

  /**
   * @brief Beállítja az aktív fifo-t.
   *
   */
  void setActiveQueue(Queue<Component>* newActiveQueue) { activeQueue = newActiveQueue; }

  /**
   * @brief Hozzáadja az aktív sorhoz az áramköri elemet.
   *
   */
  void addToActiveQueue();

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  /**
   * @brief Virtuális destruktor öröklés miatt.
   *
   */
  virtual ~Component() {}

};
class InputComponent : virtual public Component {
protected:
  /**
   * @brief A bemeneti pin-ek száma.
   */
  size_t inPinCount;
  /**
   * @brief A bemeneti pin-ek tömbje. Az index jelentést a specifikált alkatrész adja meg.
   */
  InputPin* inPins;
  size_t* inNodeIDs;

public:
  /**
   * @brief Létrehozza a bemeneti pin-ek tömbjét.
   *
   * @param inCount A bemeneti pin-ek száma.
   */
  InputComponent(size_t inCount);

  void setInNodeID(size_t at, size_t id);
  bool connectedToNodeIn(size_t id);
  void printInConnectedNodes(std::ostream& os) const;

  void resetForSimulation();

  /**
   * @brief Növeli az aktív lábak számát, és aktivizálja az áramköri elemet, ha eléri a maximumot.
   *
   */
  void activateIfReady();

  /**
   * @brief Visszaadja a bemeneti pin-ek tömbjének címét.
   *
   */
  InputPin* getInPinsBaseAdress() const { return inPins; }

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  /**
   * @brief Törli a bemeneti pin-ek tömbjét.
   *
   */
  virtual ~InputComponent();

};
class OutputComponent : virtual public Component {
protected:
  /**
   * @brief A kimeneti pin-ek száma.
   */
  size_t outPinCount;
  /**
   * @brief A kimeneti pin-ek tömbje.  Az index jelentést a specifikált alkatrész adja meg.
   *
   */
  OutputPin* outPins;
  size_t* outPinIDs;

public:
  /**
   * @brief Létrehozza a kimeneti pin-ek tömbjét.
   *
   * @param outCount A kívánt kimeneti pin-ek száma.
   */
  OutputComponent(size_t outCount);

  /**
   * @brief Összeköti a megadott kimeneti pin-jét egy másik áramköri elem bemeneti pin-jével.
   *
   * @param outPinIndex A kimeneti pin indexe.
   * @param component Amivel össze szeretnénk kötni.
   * @param inPinIndex A bemeneti pin indexe.
   */
  void connectTo(size_t outPinIndex, InputComponent* component, size_t inPinIndex);

  /**
   * @brief Kiküldi minden kimeneti lábán a lábakban tárolt jeleket.
   *
   */
  void sendOutSignals();

  /**
   * @brief
   *
   */
  OutputPin* getOutPinBaseAdress() { return outPins; }

  void setOutNodeID(size_t at, size_t id);
  bool connectedToNodeOut(size_t id);
  void printOutConnectedNodes(std::ostream& os) const;

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  /**
   * @brief Törli a kimeneti pin-ek tömbjét.
   *
   */
  virtual ~OutputComponent();

};
class IOComponent : public InputComponent, public OutputComponent {
public:
  /**
   * @brief Lértehozza a lábakat.
   *
   * @param inCount Bemeneti lábak száma.
   * @param outCount Kimeneti lábak száma.
   */
  IOComponent(size_t inCount, size_t outCount) : InputComponent(inCount), OutputComponent(outCount) {}

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  bool connectedToNodes(size_t connectedNode1, size_t connectedNode2);
  void printConnectedNodes(std::ostream& os) const;

  /**
   * @brief Virtuális destruktor, mert öröklés.
   *
   */
  virtual ~IOComponent() {}
};
#endif
