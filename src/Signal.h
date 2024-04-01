#ifndef _SIGNAL_H
#define _SIGNAL_H


class Signal {
  bool signal;

public:
  Signal(bool baseValue = false) : signal(baseValue) {}

  void setSignal(bool newValue) { signal = newValue; }
  bool getSignal() const { return signal; }

  void flipSignal() { signal = !signal; }
};
#endif
