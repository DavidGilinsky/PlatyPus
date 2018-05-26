//
// Created by gilinsky on 5/26/18.
//

#include <csignal>
#include <iostream>
#include "osSignals.h"

void osSignals::registerAll()
{
    int signals[] =
    {
            SIGHUP,
            SIGINT,
            SIGQUIT,
            SIGILL,
            SIGABRT,
            SIGFPE,
            SIGKILL,
            SIGSEGV,
            SIGPIPE,
            SIGALRM,
            SIGTERM
    };

    for(int count = 0;
        count < sizeof(signals)/sizeof(signals[0]);
        count++)
    {
        std::cout << signals[count]<< "\n";

    }


}
