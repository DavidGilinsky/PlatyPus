//
// Created by gilinsky on 10/5/17.
//

#include <arm_neon.h>
#include <netinet/in.h>

#ifndef PLATYPUS_NODE_MANAGER_H
#define PLATYPUS_NODE_MANAGER_H

#endif //PLATYPUS_NODE_MANAGER_H

struct platyNode {
    int nodeID;
    char nodeName[80];
    char nodeAddress[INET6_ADDRSTRLEN];
    bool nodeAlive;
    time_t nodeLastReached;
    bool nodeSelf;
};

struct platyNodeList {
    bool firstNode;
    bool lastNode;
    platyNode self;
    platyNode nextNode;
    platyNode prevNode;
};
