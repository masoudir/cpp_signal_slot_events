#include <iostream>
#include <thread>
#include "unistd.h"

#define EVENT_LOG
#include "lib/event.hpp"



void my_slot()
{
    std::cout << "slot executed" << std::endl;
}



int main()
{
    std::cout << "Hello World!" << std::endl;
    Signal my_signal("sig1");

    // For enabling event-based programming (By default this is Enabled and does not need this line)
    Event::enable_all_events();

    std::thread th(&Event::event_checker, Event("event1", &my_signal, my_slot));

    sleep(3);
    std::cout << "fire!" << std::endl;
    my_signal.fire();

    sleep(3);
    std::cout << "fire!" << std::endl;
    my_signal.fire();
    sleep(3);

    std::cout << "bye!" << std::endl;

    // If you want to event thread be running yet
    th.join();

    // If you want to close the application
    Event::disable_all_events();

    return 0;
}
