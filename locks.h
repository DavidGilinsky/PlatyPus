//
// Created by gilinsky on 10/6/17.
//


#ifndef PLATYPUS_LOCKS_H
#define PLATYPUS_LOCKS_H


#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <atomic>

//define the locks used to control access to data structures
//Use mutex locks to enable the use of pthread_mutex_timedlock

std::mutex nodeArrayLock;
std::mutex nodeStructLock;

#endif //PLATYPUS_LOCKS_H

