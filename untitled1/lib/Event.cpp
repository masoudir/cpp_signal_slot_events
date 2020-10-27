#include "Event.h"
#include "forward_list"


void EventClass::event_checker() {
    while (Status.isEventEnabled) {
        if (signal->get() && !Status.isResponseInProcess) {
            Status.count++;
            Status.isResponseInProcess = true;
#ifdef EVENT_LOG
            std::cout << "Event: Calling slot started. Trig NO: " << Status.count << std::endl;
#endif
            Status.responseFailed = !slot_execute();
            Status.isResponseInProcess = false;
#ifdef EVENT_LOG
            std::cout << "Event: Slot finished. Trig NO: " << Status.count << std::endl;
#endif
        }
    }
}

int EventClass::slot_execute() {
    try {
        std::cout << "";
        slot_function();
        return true;
    }
    catch (const char *err) {
        std::cerr << "error:" << err << std::endl;
        return false;
    }

}


EventStatus EventClass::getStatus() {
    return Status;
}

EventClass::EventClass(SignalClass *sig, void (*slot)(void))
        : Status({0, false, false, false}) {
    slot_function = slot;
    signal = sig;
    Status.isEventEnabled = true;
#ifdef EVENT_LOG
    std::cout << "Event has been established." << std::endl;
#endif
}




