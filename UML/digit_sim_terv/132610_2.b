class Queue
!!!161026.cpp!!!	operator =(in source : Queue) : Queue
  QueueMember<T>* moving = source.begin;
  while (moving != nullptr) {
    this->put(moving->pointingTo);
    moving = moving->nextMember;
  }
  return *this;
!!!161282.cpp!!!	Queue(in source : Queue)
  *this = source;
!!!161410.cpp!!!	put(inout added : T) : void
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
  siz++;
!!!161538.cpp!!!	get() : T
  if (siz > 0) {
    QueueMember<T>* returnedMember = begin;
    begin = begin->nextMember;
    T* returned = returnedMember->pointingTo;
    delete returnedMember;
    siz--;
    return returned;
  }
  return nullptr;
!!!161666.cpp!!!	isEmpty() : bool
  return siz == 0;
!!!161794.cpp!!!	clear() : void
  if (ownsMembers) {
    while (!isEmpty()) {
      delete get();
    }
  }
  else {
    while (!isEmpty()) {
      get();
    }
  }
!!!161922.cpp!!!	size() : size_t
  return siz;
!!!162050.cpp!!!	~Queue()
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

