//
// Created by gilinsky on 10/5/17.
//

#include <cstdio>
#include <ctime>
#include <iostream>
#include <thread>

#include "node_manager.h"
#include "main.h"

using namespace std;

//Initialize global variables

volatile int sig_caught=0;

// Setup memory for structures to hold node information.
struct platyNode **node_array = static_cast<platyNode **>(malloc(10 * sizeof(struct platyNode *)));

int main() {
    int return_value=0;

    std::cout << "Hello, World!" << std::endl;

    return_value=register_signals();

    if(return_value!=0){
        printf("Failed to register %d\n",return_value);
    } else {
        printf("Signals registered\n");
    }

    // Populate each element of node_array with a pointer to a block of memory to hold a node structure
     for (int i = 0; i < 10; i++) {
         node_array[i] = static_cast<platyNode *>(malloc(sizeof(struct platyNode)));
     }

    //test node stuff
     node_array[0]->nodeID=1;

     for (int i=0; i<10; i++) {
         printf("Node %d ID: %d\n",i,node_array[i]->nodeID);
     }

    printf("Node 0 ID %d\n", returnNodeID(node_array,0));

    thread net_listener(tcp_listener);

    net_listener.detach();

    printf("Started listener at id %d\n",net_listener.get_id());

    while(1){

    }

    return 0;
}

