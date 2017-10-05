//
// Created by gilinsky on 10/5/17.
//

#include <cstdio>
#include <iostream>
#include <thread>
#include "main.h"

using namespace std;

volatile int sig_caught=0;

int main() {
    int return_value=0;

    std::cout << "Hello, World!" << std::endl;

    return_value=register_signals();
    if(return_value!=0){
        printf("Failed to register %d\n",return_value);
    }


    thread net_listener(tcp_listener);

    net_listener.detach();

    printf("Started listener at id %d\n",net_listener.get_id());

    while(1){

    }

    return 0;
}

