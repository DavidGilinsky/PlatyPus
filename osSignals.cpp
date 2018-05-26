//
// Created by gilinsky on 5/26/18.
//

#include <csignal>
#include <iostream>
#include "osSignals.h"

static void osSignals::sig_hup() {

}
static void osSignals::sig_int() {

}
static void osSignals::sig_quit() {

}
static void osSignals::sig_ill() {

}
static void osSignals::sig_abrt() {

}
static void osSignals::sig_fpe() {

}
static void osSignals::sig_kill() {

}
static void osSignals::sig_segv() {

}
static void osSignals::sig_pipe() {

}
static void osSignals::sig_alrm() {

}
static void osSignals::sig_term() {

}


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

        std::cout << "Registering signal: " << signals[count] << "\n";
        if(signal(signals[count], handle)==SIG_ERR)
        {
            throw "Error registering signal!";
        }

    }


}

static void osSignals::handle(int signo)
{
    switch(signo){
        case SIGHUP : sig_hup();
        case SIGINT : sig_int();
        case SIGQUIT : sig_quit();
        case SIGILL : sig_ill();
        case SIGABRT : sig_abrt();
        case SIGFPE : sig_fpe();
        case SIGKILL : sig_kill();
        case SIGSEGV : sig_segv();
        case SIGPIPE : sig_pipe();
        case SIGALRM : sig_alrm();
        case SIGTERM : sig_term();
        default : return;
    }
}
