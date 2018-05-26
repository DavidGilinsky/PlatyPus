//
// Created by gilinsky on 5/26/18.
//

#ifndef PLATYPUS_OSSIGNALS_H
#define PLATYPUS_OSSIGNALS_H


class osSignals {
private:
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

public:
    void handle(int signal_number);
    void registerAll();
};


#endif //PLATYPUS_OSSIGNALS_H
