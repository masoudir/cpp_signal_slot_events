#include <iostream>
#include <thread>
#include "unistd.h"

#define EVENT_LOG
#include "lib/event.hpp"




int h[6];

void pr()
{
    std::cout << "pr executed" << std::endl;
//    std::cout << (h[0]) << std::endl;
}



int main()
{
    std::cout << "Hello World!" << std::endl;
    Signal sig("sig1");

    std::thread th(&Event::event_checker, Event("event1", &sig, pr));
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
    th.join();
    return 0;
}
