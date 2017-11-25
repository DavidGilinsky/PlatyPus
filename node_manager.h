//
// Created by gilinsky on 10/5/17.
//

#ifndef PLATYPUS_NODE_MANAGER_H
#define PLATYPUS_NODE_MANAGER_H

#include <arm_neon.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#include "sensor_data.h"

struct platyNode {
    time_t nodeCreated;
    char nodeID;
    char nodeName[80];
    char nodeIPAddress[INET6_ADDRSTRLEN];
    unsigned char nodeMACAddress[6];
    ifaddrs nodeInterface;
    bool nodeAlive;
    time_t nodeLastReached;
    bool nodeSelf;
    int nodeTxSocket;
    int nodeRxSocket;
    bool nodeJeopardy;
    bool nodeStructIncoherent;
    bool haveDisplay;
    sensorData sensor;
};



#endif //PLATYPUS_NODE_MANAGER_H
