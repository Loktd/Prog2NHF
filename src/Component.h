#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Pin.h"
#include "Queue.h"
#include "Exceptions.h"


class InputPin;
class OutputPin;


class Component {
protected:
  /**
   * @brief Az aktív sor, amihez kell hozzáadni, ha ki kell értékelni az elemet, azaz végrehajtani a funkcióját.
   *
   */
  Queue<Component>* activeQueue;

  /**
   * @brief Le lett-e szimulálva az áramkör elem. (true = igen, false = nem)
   *
   */
  bool simulated;

public:
  /**
   * @brief Felparaméterezi az aktív FIFO-t.
   *
   * @param newActiveQueue Az elem aktív FIFO-ja, NULL ha nincs neki megadva még.
   */
  Component(Queue<Component>* newActiveQueue = nullptr);

  /**
   * @brief Beállítja az aktív FIFO-t.
   *
   */
  void setActiveQueue(Queue<Component>* newActiveQueue);

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
   * @brief Beállítja, hogy szimulálva volt, az elem;
   *
   */
  void gotSimulated();

  /**
   * @brief Visszaadja, hogy le volt-e szimulálva az elem.
   *
   * @return true = már le volt szimulálva ;
   * @return false = még nem volt leszimulálva
   */
  bool wasSimulated();

  /**
   * @brief Reseteli a szimuláltság státuszát.
   *
   */
  void resetSimulted();

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
   *
   */
  size_t inputPinCount;

  /**
   * @brief A bemeneti pin-ek tömbje. Az index jelentést a specifikált alkatrész adja meg.
   *
   */
  InputPin* inputPins;

  /**
   * @brief A bemeneti csomópontok ID-jai kiolvasáshoz.
   *
   */
  size_t* inputNodeIDs;

public:
  /**
   * @brief Létrehozza a bemeneti pin-ek tömbjét.
   *
   * @param inputCount A bemeneti pin-ek száma.
   */
  InputComponent(size_t inputCount);

  /**
   * @brief Reseteli a bemeneti pin-ek státuszát szimulációhoz.
   *
   */
  void resetForSimulation();

  /**
   * @brief Ellenőrzi hogy minden bemeneti pin aktív-e, és berakja az aktív FIFO-ba, ha igen.
   *
   */
  void activateIfReady();

  /**
   * @brief Vissza adja a kívánt indexű bemeneti pin címét, ha létezik.
   *
   * @param idx A kívánt indexű pin.
   * @return InputPin* Az adott indexű pin.
   * @exception Ha túlindexelünk, akkor dob std::out_of_range-t.
   */
  InputPin* getInputPinByIndex(size_t idx) const;

  /**
   * @brief Beállítja egy bemeneti csompópont ID-t kiolvasáshoz.
   *
   * @param at A beállított bemenet indexe.
   * @param ID A beállított csomópont ID.
   * @exception Ha túlindexelünk, akkor dob egy std::out_of_range-t.
   */
  void setInputNodeID(size_t at, size_t ID);

  /**
   * @brief Ellenőri, hogy kapcsolódik-e egy adott csomóponthoz a bemenetén.
   *
   * @param ID A keresett csomópont ID-ja.
   * @return true = kapcsolódik hozzá a bemeneten ;
   * @return false = nem kapcsolódik hozzá a bemeneten
   */
  bool isConnectedToNodeOnInput(size_t ID);

  /**
   * @brief Kiírja a bemeneten csatlakoztatott csomópontok ID-ját.
   *
   * @param os A kimeneti stream, ahova akarjuk kiírni.
   */
  void printConnectedInputNodes(std::ostream& os) const;

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
   *
   */
  size_t outputPinCount;

  /**
   * @brief A kimeneti pin-ek tömbje. Az index jelentést a specifikus alkatrész adja meg.
   *
   */
  OutputPin* outputPins;

  /**
   * @brief A kimenet csomópontok ID-jai kiolvasáshoz.
   *
   */
  size_t* outputPinIDs;

public:
  /**
   * @brief Létrehozza a kimeneti pin-ek és csomópont ID-k tömbjét.
   *
   * @param outputCount A kívánt kimeneti pin-ek száma.
   */
  OutputComponent(size_t outputCount);

  /**
   * @brief Összeköti a megadott kimeneti pin-jét egy másik áramköri elem bemeneti pin-jével.
   *
   * @param outputPinIndex A kimeneti pin indexe.
   * @param component Amivel össze szeretnénk kötni.
   * @param inputPinIndex A bemeneti pin indexe.
   *
   * @exception Ha a kimeneti vagy bemeneti pin-ek tömbjén kívül indexelünk, akkor dob egy std::out_of_range-t.
   */
  void connectToInputPin(size_t outputPinIndex, InputComponent* component, size_t inputPinIndex);

  /**
   * @brief Kiküldi minden kimeneti lábán a lábakban tárolt jeleket.
   *
   */
  void sendOutSignals();

  /**
   * @brief Vissza adja a kívánt indexű kimeneti pin címét, ha létezik.
   *
   * @param idx A kívánt indexű pin.
   * @return OutputPin* Az adott indexű pin.
   * @exception Ha túlindexelünk, akkor dob std::out_of_range-t.
   */
  OutputPin* getOutputPinByIndex(size_t idx);

  /**
   * @brief Beállítja a kimeneti csomópont ID-t kiolvasáshoz.
   *
   * @param at A beállított kimenet indexe.
   * @param ID A beállított csomópont ID.
   * @exception Ha túlindexelünk, akkor dob egy std::out_of_range-t.
   */
  void setOutputNodeID(size_t at, size_t ID);

  /**
   * @brief Ellenőri, hogy kapcsolódik-e egy adott csomóponthoz a kimenetén.
   *
   * @param ID A keresett csomópont ID-ja.
   * @return true = kapcsolódik hozzá a kimeneten ;
   * @return false = nem kapcsolódik hozzá a kimeneten
   */
  bool isConnectedToNodeOnOutput(size_t ID);

  /**
   * @brief Kiírja a kimeneten csatlakoztatott csomópontok ID-ját.
   *
   * @param os A kimeneti stream, ahova akarjuk kiírni.
   */
  void printConnectedOutputNodes(std::ostream& os) const;

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
   * @brief Létrehozza az IO elemet, mindkét oldali tulajdonságaival.
   *
   * @param inputCount Bemeneti lábak száma.
   * @param outputCount Kimeneti lábak száma.
   */
  IOComponent(size_t inputCount, size_t outputCount);

  /**
   * @brief Ellenőrzi, hogy kapcsolódik-e két csomóponthoz ellentétes oldalról (egyik kimeneti, másik bemeneti, vagy fordítva).
   *
   * @param NodeID1 Az egyik csomópont ID-ja.
   * @param NodeID2 A másik csomópont ID-ja.
   * @return true = kapcsolódik ezekhez ;
   * @return false = nem kapcsolódik ezekhez
   */
  bool isConnectedToNodes(size_t NodeID1, size_t NodeID2);

  /**
   * @brief Kiírja a kapcsolódó csomópontok ID-jait mind bemenet, mind kimenetre (előbb bemenet, utána kimenet).
   *
   * @param os A kimeneti stream, ahova akarjuk kiírni.
   */
  void printConnectedNodes(std::ostream& os) const;

  /**
   * @brief Végrehajtja a funkcióját az áramköri elemnek. Leszármazottban konkretizálva.
   *
   */
  virtual void executeFunction() = 0;

  /**
   * @brief Virtuális destruktor, mert öröklés.
   *
   */
  virtual ~IOComponent() {}
};
#endif
