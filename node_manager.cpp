//
// Created by gilinsky on 10/5/17.
//

#include <cstring>
#include <ctime>
#include <net/if.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <ifaddrs.h>
#include <cstdio>
#include <arpa/inet.h>


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

int populateNodeSelf(platyNode **nodeArray)
{
    ifaddrs *addrs,*tmp;

    getifaddrs(&addrs);
    tmp = addrs;

    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            struct sockaddr_in *pBc = (struct sockaddr_in *) tmp->ifa_ifu.ifu_broadaddr;
            printf("%s: %s %s %d\n",
                   tmp->ifa_name,
                   inet_ntoa(pAddr->sin_addr),
                   inet_ntoa(pBc->sin_addr),
                   (tmp->ifa_flags&IFF_UP));
            if(strstr(tmp->ifa_name,"lo")==0) {
                if((tmp->ifa_flags&IFF_UP)==1){
                    nodeArray[0]->nodeInterface.ifa_name =tmp->ifa_name;
                    nodeArray[0]->nodeInterface.ifa_addr =tmp->ifa_addr;
                    nodeArray[0]->nodeInterface.ifa_ifu.ifu_broadaddr =tmp->ifa_ifu.ifu_broadaddr;

                    struct sockaddr_in *pIfc = (struct sockaddr_in *)nodeArray[0]->nodeInterface.ifa_addr;
                    printf("Live Interface %s found - %s.\n",
                           nodeArray[0]->nodeInterface.ifa_name,
                           inet_ntoa(pIfc->sin_addr));
                }
            }
        }

        tmp = tmp->ifa_next;
    }

freeifaddrs(addrs);
}
