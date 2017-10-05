//
// Created by gilinsky on 10/5/17.
//

#include <csignal>

#ifndef PLATYPUS_MAIN_H
#define PLATYPUS_MAIN_H

#endif //PLATYPUS_MAIN_H

extern volatile sig_atomic_t sig_caught;

extern void sig_handler(int);
extern int register_signals();
extern int tcp_listener();
