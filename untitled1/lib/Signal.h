
#ifndef SIGNAL_H
#define SIGNAL_H
#include <iostream>

#define EVENT_LOG

class SignalClass{
public:
    SignalClass();

    void fire();
    bool get();
private:
    bool isFired;
};

#endif //SIGNAL_H
