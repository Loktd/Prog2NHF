#ifndef _QUEUE_H
#define _QUEUE_H


template<class T>
class Queue {
  private:
    bool ownsMembers;


  public:
    inline Queue(bool owner = false);

    inline Queue(const Queue<T> & source);

    inline Queue<T> & operator =(const Queue<T> & source);

    inline void put(const T * & added);

    inline void deleteQueue();

    inline T * get();

    inline ~Queue();


  private:
    QueueMember<T> * queue;

};
template<class T>
inline Queue<T>::Queue(bool owner){
}

template<class T>
inline Queue<T>::Queue(const Queue<T> & source){
}

template<class T>
inline void Queue<T>::put(const T * & added) {
}

template<class T>
inline void Queue<T>::deleteQueue() {
}

template<class T>
inline T * Queue<T>::get() {
}

template<class T>
inline Queue<T>::~Queue(){
}

template<class T>
struct QueueMember {
    QueueMember<T> * nextMember;

    T * pointingTo;

};
#endif
