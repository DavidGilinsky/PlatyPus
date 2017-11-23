//
// Created by gilinsky on 10/5/17.
//

#include <cstring>
#include <ctime>

#include "node_manager.h"

platyNode *nodeCreate(){
    platyNode * node;
    node = new platyNode;
    node->nodeCreated=time(0);
    return node;

};

int AddNode(platyNode *nodeArray, platyNode node){
    return 0;
}

int DeleteNode(platyNode *nodeArray, int nodeID){
    return 0;
}

int resetNodeArray(platyNode *nodeArray){
    memset(nodeArray,255,255*sizeof(nodeArray));
}

int returnNodeID(platyNode **nodeArray, int element)
{
    return(nodeArray[element]->nodeID);
}
