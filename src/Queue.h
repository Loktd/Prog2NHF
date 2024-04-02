#ifndef _QUEUE_H
#define _QUEUE_H

typedef long long unsigned int size_t;

template<class T>
struct QueueMember {
  /**
   * @brief A következő elem címe a fifo-ban.
   */
  QueueMember<T>* nextMember;
  /**
   * @brief A mutatott elem.
   */
  T* pointingTo;
};

template<class T>
class Queue {
  /**
   * @brief Birtokolja-e az elemeit, azaz destruktorban fel kell-e szabadítania a tárolt tagokat is a fifo tárolóival.
   * (true = igen, false = nem)
   */
  bool ownsMembers;

  /**
   * @brief A fifo elejére mutató. (kivétel és felszabadításhoz)
   */
  QueueMember<T>* begin;
  /**
   * @brief A fifo végére mutató. (könnyű beszúráshoz)
   *
   */
  QueueMember<T>* end;

  /**
   * @brief Csak a másolás megengedett, emiatt ezt priváttal letiltjuk.
   *
   * @param source A másolás forrása, a mutatott tagokat ez a fifo nem birtokolja.
   * @return Queue<T>& Minta szerint van csak, igazi értelme nincsen.
   */
  Queue<T>& operator=(const Queue<T>& source);

public:
  /**
   * @brief Beállítja az üres fifo állapotát.
   *
   * @param owner Tulaja-e az elemeknek, azaz fel kell majd szabadítani a mutatott objektumokat-e.
   */
  Queue(bool owner = true) : ownsMembers(owner), begin(nullptr), end(nullptr) {}

  /**
   * @brief Másolást teszi lehetővé, hogy ideiglenesen valamit tudjunk futtatni a fifo-n, a tagokat nem birtokolja.
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
   * @brief Detruktor, mely felszabadítja a tárolt elemeket, attól függően, hogy birtokolja-e őket.
   *
   */
  ~Queue();
};


template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& source)
{
  QueueMember<T>* moving = source.begin;
  while (moving != nullptr) {
    this->put(moving->pointingTo);
    moving = moving->nextMember;
  }
  return *this;
}
template<class T>
Queue<T>::Queue(const Queue<T>& source)
{
  ownsMembers = false;
  begin = nullptr;
  end = nullptr;
  *this = source;
}
template<class T>
void Queue<T>::put(T* added)
{
  if (begin == nullptr) {
    begin = new QueueMember<T>;
    begin->pointingTo = added;
    begin->nextMember = nullptr;
    end = begin;
  }
  else {
    QueueMember<T>* newMember = new QueueMember<T>;
    newMember->pointingTo = added;
    newMember->nextMember = nullptr;
    end->nextMember = newMember;
    end = newMember;
  }
}
template<class T>
T* Queue<T>::get()
{
  QueueMember<T>* returnedMember = begin;
  begin = begin->nextMember;
  T* returned = returnedMember->pointingTo;
  delete returnedMember;
  return returned;
}

template<class T>
Queue<T>::~Queue() {
  if (ownsMembers) {
    while (begin != nullptr) {
      QueueMember<T>* next = begin->nextMember;
      delete begin->pointingTo;
      delete begin;
      begin = next;
    }
  }
  else {
    while (begin != nullptr) {
      QueueMember<T>* next = begin->nextMember;
      delete begin;
      begin = next;
    }
  }

}
#endif
