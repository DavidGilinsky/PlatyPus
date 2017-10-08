//
// Created by gilinsky on 10/5/17.
//

#ifndef PLATYPUS_NODE_MANAGER_H
#define PLATYPUS_NODE_MANAGER_H

#include <arm_neon.h>
#include <netinet/in.h>


typedef struct {
    time_t nodeCreated;
    char nodeID;
    char nodeName[80];
    char nodeAddress[INET6_ADDRSTRLEN];
    bool nodeAlive;
    time_t nodeLastReached;
    bool nodeSelf;
    int nodeTxSocket;
    int nodeRxSocket;
    bool nodeJeopardy;
    bool nodeStructIncoherent;
} platyNode;



#endif //PLATYPUS_NODE_MANAGER_H
