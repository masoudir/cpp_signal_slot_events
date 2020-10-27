#ifndef EVENT_H
#define EVENT_H
#include "thread"
#include "Signal.h"
#include <iostream>


//#define EVENT_LOG

struct EventStatus{
    unsigned int count;
    bool isEventEnabled;
    bool isResponseInProcess;
    bool responseFailed;
};





class EventClass {
public:
    EventClass(SignalClass *sig, void (*handler)(void));
    EventStatus getStatus();
    void event_checker();

private:
    EventStatus Status;
    SignalClass *signal;
    int slot_execute();
    void (*slot_function)(void);
};

#endif // EVENT_H
