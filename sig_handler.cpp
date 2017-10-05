//
// Created by gilinsky on 10/5/17.
//

#include <bits/signum.h>
#include "sig_handler.h"
#include "main.h"


int register_signals(){
    if(signal(SIGHUP, sig_handler)==SIG_ERR){
        return SIGHUP;
    }
    if(signal(SIGINT, sig_handler)==SIG_ERR){
        return SIGINT;
    }
    if(signal(SIGQUIT, sig_handler)==SIG_ERR){
        return SIGQUIT;
    }
    if(signal(SIGILL, sig_handler)==SIG_ERR){
        return SIGILL;
    }
    if(signal(SIGABRT, sig_handler)==SIG_ERR){
        return SIGABRT;
    }
    if(signal(SIGFPE, sig_handler)==SIG_ERR){
        return SIGFPE;
    }
    if(signal(SIGKILL, sig_handler)==SIG_ERR){
        return SIGKILL;
    }
    if(signal(SIGSEGV, sig_handler)==SIG_ERR){
        return SIGSEGV;
    }
    if(signal(SIGPIPE, sig_handler)==SIG_ERR){
        return SIGPIPE;
    }
    if(signal(SIGALRM, sig_handler)==SIG_ERR){
        return SIGALRM;
    }
    if(signal(SIGTERM, sig_handler)==SIG_ERR){
        return SIGTERM;
    }
    return 0;
}

void sig_hup(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_int(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_quit(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_ill(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_abrt(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_fpe(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_kill(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_segv(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_pipe(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_alrm(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}
void sig_term(int signo) {
    sig_caught = signo;

    sig_caught = 0;
}

void sig_handler(int signo)
{
    switch(signo){
        case SIGHUP : sig_hup(signo);
        case SIGINT : sig_int(signo);
        case SIGQUIT : sig_quit(signo);
        case SIGILL : sig_ill(signo);
        case SIGABRT : sig_abrt(signo);
        case SIGFPE : sig_fpe(signo);
        case SIGKILL : sig_kill(signo);
        case SIGSEGV : sig_segv(signo);
        case SIGPIPE : sig_pipe(signo);
        case SIGALRM : sig_alrm(signo);
        case SIGTERM : sig_term(signo);
        default : return;
    }
}


