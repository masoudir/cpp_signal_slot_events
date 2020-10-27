#include <iostream>
#include <thread>
#include "unistd.h"

#define EVENT_LOG
#include "lib/Event.h"




int h[6];

void pr()
{
    std::cout << "pr executed" << std::endl;
//    std::cout << (h[0]) << std::endl;
}



int main()
{
    std::cout << "Hello World!" << std::endl;
    SignalClass sig;

    std::thread th(&EventClass::event_checker, EventClass(&sig, pr));
    {
        sleep(3);
        std::cout << "trig!" << std::endl;
        sig.fire();
        sleep(3);
        std::cout << "untrig!" << std::endl;
    }
    {
        sleep(3);
        std::cout << "trig!" << std::endl;
        sig.fire();
        sleep(3);
        std::cout << "untrig!" << std::endl;
    }
    std::cout << "bye!" << std::endl;
    return 0;
}
