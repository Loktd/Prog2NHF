#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Queue.hpp"
#include "Exceptions.hpp"
#include "../test/memtrace.h"


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
  bool gotSimulated;

public:
  /**
   * @brief Felparaméterezi aktív FIFO-val ha megadjuk, amúgy csak létrehozzuk.
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
   * @brief Visszaadja, hogy le volt-e szimulálva az elem.
   *
   * @return true = már le volt szimulálva ;
   * @return false = még nem volt leszimulálva
   */
  bool simulated();

  /**
   * @brief Beállítja hogy szimulálva volt, az elem.
   *
   */
  void setSimulated();

  /**
   * @brief Reseteli a szimuláltság státuszát.
   *
   */
  void resetSimulted();

  /**
   * @brief Virtuális destruktor öröklés miatt.
   *
   */
  virtual ~Component();
};

#endif