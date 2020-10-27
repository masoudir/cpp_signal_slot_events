/****************************************************************************
 *
 * Copyright (c) 2020, 2021 Masoud Iranmehr. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file event.hpp
 * C++ event-based programming tools
 *
 * @author Masoud Iranmehr <masoud.iranmehr@gmail.com>
 */

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <thread>
#include <ctime>


struct EventStatus {
    unsigned int count;
    bool isEventEnabled;
    bool isResponseInProcess;
    bool responseFailed;
};


class Signal {
public:
    Signal(const char *name);

    void fire();

    bool get();

private:
    bool isFired;
    const char *sigName;
};

class Event {
public:
    Event(const char *name, Signal *sig, void (*handler)(void));

    EventStatus getStatus();

    void event_checker();

private:
    EventStatus Status;
    Signal *signal;
    const char *eventName;

    int slot_execute();

    void (*slot_function)(void);
};


void Event::event_checker() {
    while (Status.isEventEnabled) {
        if (signal->get() && !Status.isResponseInProcess) {
            Status.count++;
            Status.isResponseInProcess = true;
#ifdef EVENT_LOG
            time_t now = time(0);
            std::cout << eventName << ": Slot started at " << ctime(&now) << std::endl;
#endif
            Status.responseFailed = !slot_execute();
            Status.isResponseInProcess = false;
#ifdef EVENT_LOG
            now = time(0);
            std::cout << eventName << ": Slot finished at " << ctime(&now) << std::endl;
#endif
        }
    }
}

int Event::slot_execute() {
    try {
        std::cout << "";
        slot_function();
        return true;
    }
    catch (const char *err) {
#ifdef EVENT_LOG
        time_t now = time(0);
        std::cerr << eventName << ": Error in running slot. Error: at " << ctime(&now) << " Error:" << err << std::endl;
#endif
        return false;
    }

}


EventStatus Event::getStatus() {
    return Status;
}

Event::Event(const char *name, Signal *sig, void (*slot)(void))
        : Status({0, false, false, false}) {
    slot_function = slot;
    signal = sig;
    eventName = name;
    Status.isEventEnabled = true;
#ifdef EVENT_LOG
    time_t now = time(0);
    std::cout << eventName << ": Established at " << ctime(&now) << std::endl;
#endif
}


Signal::Signal(const char *name) : isFired(false) {
    sigName = name;
}

void Signal::fire() {
    if (!isFired) {
#ifdef EVENT_LOG
        time_t now = time(0);
        std::cout << sigName << ": Fired at " << ctime(&now) << std::endl;
#endif
        isFired = true;
    }

}

bool Signal::get() {
    bool status = isFired;
    isFired = false;
    return status;
}

#endif //EVENT_H
