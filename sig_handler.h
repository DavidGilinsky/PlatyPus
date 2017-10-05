//
// Created by gilinsky on 10/5/17.
//

#ifndef PLATYPUS_SIG_HANDLER_H
#define PLATYPUS_SIG_HANDLER_H

#endif //PLATYPUS_SIG_HANDLER_H

//Signal handling functions prototypes

void sig_hup(int sig_caught);
void sig_int(int sig_caught);
void sig_quit(int sig_caught);
void sig_ill(int sig_caught);
void sig_abrt(int sig_caught);
void sig_fpe(int sig_caught);
void sig_kill(int sig_caught);
void sig_segv(int sig_caught);
void sig_pipe(int sig_caught);
void sig_alrm(int sig_caught);
void sig_term(int sig_caught);

