#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <exception>


typedef long long unsigned int size_t;


template<class T>
class Queue {
  struct QueueMember {
    /**
     * @brief A következő elem címe a FIFO-ban.
     */
    QueueMember* nextMember;

    /**
     * @brief A mutatott elem.
     */
    T* storedPointer;

    /**
     * @brief Default konstruktor, ami NULL-ra állítja a tárolt pointert, amit lehet átállítani.
     *
     */
    QueueMember() : storedPointer(nullptr) {}
  };


  /**
   * @brief Birtokolja-e az elemeit, azaz destruktorban fel kell-e szabadítania a tárolt tagokat is a FIFO tárolóival.
   * (true = igen, false = nem)
   */
  bool ownsMembers;

  /**
   * @brief A FIFO elejére mutató. (kiszedés és felszabadításhoz)
   */
  QueueMember* first;
  /**
   * @brief A FIFO végére mutató. (könnyű beszúráshoz)
   *
   */
  QueueMember* last;

  /**
   * @brief Csak a másolás megengedett, emiatt ezt priváttal letiltjuk.
   *
   * @param source A másolás forrása, a mutatott tagokat ez a FIFO nem birtokolja.
   * @return Queue<T>& Minta szerint van csak, igazi értelme nincsen.
   */
  Queue<T>& operator=(const Queue<T>& source);

  /**
   * @brief A tárolt elemek száma, könnyű méret olvasáshoz.
   *
   */
  size_t siz;

public:
  /**
   * @brief Beállítja az üres FIFO állapotát.
   *
   * @param owner Tulaja-e az elemeknek, azaz fel kell majd szabadítani a mutatott objektumokat-e.
   */
  Queue(bool owner = false);

  /**
   * @brief Másolást teszi lehetővé, hogy ideiglenesen valamit tudjunk futtatni a FIFO-n, a tagokat nem birtokolja.
   *
   * @param source A másolás forrása.
   */
  Queue(const Queue<T>& source);

  /**
   * @brief Berak egy tagot a sor végére.
   *
   * @param added A hozzáadott tag.
   */
  void put(T* added);

  /**
   * @brief Kivesz a sor elejéről egy tagot.
   *
   * @return T* A soron következő tag.
   */
  T* get();

  /**
   * @brief Megmondja, hogy üres-e a FIFO.
   *
   * @return true = üres a FIFO ;
   * @return false = nem üres a FIFO
   */
  bool isEmpty();

  /**
   * @brief Kiürítí a FIFO-t, ha tulaj, akkor törli a memóriát is.
   *
   */
  void clear();

  /**
   * @brief Visszaadja a FIFO elemszámát.
   *
   * @return size_t A FIFO mérete.
   */
  size_t size() const;

  /**
   * @brief Detruktor, mely felszabadítja a tárolt elemeket, attól függően, hogy birtokolja-e őket.
   *
   */
  ~Queue();

  class iterator {
    /**
     * @brief A FIFO tag, amire mutat.
     *
     */
    QueueMember* pointingTo;
  public:
    /**
     * @brief Default konstruktor, a végét adja.
     *
     */
    iterator() : pointingTo(nullptr) {}

    /**
     * @brief Nem default konstruktor, az elejét adja.
     *
     * @param queue A FIFO, aminek az eleje kell.
     */
    iterator(const Queue& queue) : pointingTo(queue.first) {}

    /**
     * @brief Preinkremens iterátorra.
     *
     * @return iterator& Az iterátorra referencia láncoláshoz.
     * @exception Ha túl akarunk menni a végen, akkor dob egy std::out_of_range-t.
     */
    iterator& operator++() {
      if (pointingTo == nullptr)
        throw std::out_of_range("Queue iterator tried going after end...");
      pointingTo = pointingTo->nextMember;
      return *this;
    }

    /**
     * @brief Postinkremens iterátorra.
     *
     * @return iterator A post szerep miatt adja vissza a kezdetit.
     */
    iterator operator++(int) {
      iterator tmp = *this;
      operator++();
      return tmp;
    }

    /**
     * @brief Egyenlőség operátor iterátorra.
     *
     * @param it Amivel hasonlítjuk.
     * @return true = egyenlőek ;
     * @return false = nem egyenlőek
     */
    bool operator==(const iterator& it) {
      return pointingTo == it.pointingTo;
    }

    /**
     * @brief Nem egyenlő operátor iterátorra.
     *
     * @param it Amivel hasonlítjuk.
     * @return true = nem egyenlőek ;
     * @return false = egyenlőek
     */
    bool operator!=(const iterator& it) {
      return !(*this == it);
    }

    /**
     * @brief Az iterátoron keresztül elérni kívánt tárolt adatot adja vissza.
     *
     * @return T* A tárolt pointer.
     * @exception Ha dereferálni akarunk a végén, akkor dob egy std::out_of_range-t.
     */
    T* operator*() {
      if (pointingTo == nullptr)
        throw std::out_of_range("Queue iterator dereferenced end...");
      return pointingTo->storedPointer;
    }

    /**
     * @brief Az iterátoron keresztül elérni kívánt tárolt adat tagjainak elérését engedélyezi.
     *
     * @return T** Pointer a tárolt adat pointerére.
     * @exception Ha elérni akarunk tagot a végén, akkor dob egy std::out_of_range-t.
     */
    T** operator->() {
      if (pointingTo == nullptr)
        throw std::out_of_range("Queue iterator accessed end member...");
      return &(pointingTo->storedPointer);
    }
  };

  /**
   * @brief A FIFO elejére ad iterátort.
   *
   * @return iterator Az elejére iterátor.
   */
  iterator begin() const {
    return iterator(*this);
  }

  /**
   * @brief A FIFO végére ad iterátort.
   *
   * @return iterator A végére iterátor.
   */
  iterator end() const {
    return iterator();
  }
};

// Privát tagfüggvények

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& source)
{
  for (iterator moving = source.begin(); moving != source.end(); moving++) {
    put(*moving);
  }
  return *this;
}

// Privát vége


// Publikus tagfüggvények

template<class T>
inline Queue<T>::Queue(bool owner) : ownsMembers(owner), first(nullptr), last(nullptr), siz(0) {}

template<class T>
Queue<T>::Queue(const Queue<T>& source) : ownsMembers(false), first(nullptr), last(nullptr), siz(0)
{
  *this = source;
}

template<class T>
void Queue<T>::put(T* added)
{
  QueueMember* newMember = new QueueMember;
  newMember->storedPointer = added;
  newMember->nextMember = nullptr;

  if (first == nullptr) {
    first = newMember;
    last = newMember;
  }
  else {
    last->nextMember = newMember;
    last = newMember;
  }

  siz++;
}

template<class T>
T* Queue<T>::get()
{
  QueueMember* returnedMember = first;
  T* returned = nullptr;

  if (siz > 0) {
    if (siz > 1) {
      first = first->nextMember;
    }
    else if (siz == 1) {
      first = nullptr;
      last = nullptr;
    }
    returned = returnedMember->storedPointer;
    delete returnedMember;

    siz--;
  }

  return returned;
}

template<class T>
inline bool Queue<T>::isEmpty()
{
  return siz == 0;
}

template<class T>
inline void Queue<T>::clear()
{
  if (!ownsMembers) {
    while (!isEmpty()) {
      get();
    }
    return;
  }

  while (!isEmpty()) {
    delete get();
  }
}

template<class T>
inline size_t Queue<T>::size() const
{
  return siz;
}

template<class T>
Queue<T>::~Queue() {
  clear();
}

// Publikus vége

#endif