#include "Signal.h"



SignalClass::SignalClass() : isFired(false){

}

void SignalClass::fire() {
    if(!isFired)
        isFired = true;
#ifdef EVENT_LOG
    std::cout << "Signal: Fired " << std::endl;
#endif
}

bool SignalClass::get() {
    bool status = isFired;
    isFired = false;
    return status;
}
