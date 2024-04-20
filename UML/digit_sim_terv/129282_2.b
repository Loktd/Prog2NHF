class Queue
!!!142850.cpp!!!	operator =(in source : Queue) : Queue
  QueueMember<T>* moving = source.begin;
  while (moving != nullptr) {
    this->put(moving->pointingTo);
    moving = moving->nextMember;
  }
  return *this;
!!!143106.cpp!!!	Queue(in source : Queue)
  *this = source;
!!!143234.cpp!!!	put(inout added : T) : void
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
!!!143362.cpp!!!	get() : T
  if (siz > 0) {
    QueueMember<T>* returnedMember = begin;
    begin = begin->nextMember;
    T* returned = returnedMember->pointingTo;
    delete returnedMember;
    siz--;
    return returned;
  }
  return nullptr;
!!!143490.cpp!!!	isEmpty() : bool
  return siz == 0;
!!!143618.cpp!!!	clear() : void
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
!!!143746.cpp!!!	size() : size_t
  return siz;
!!!143874.cpp!!!	~Queue()
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

