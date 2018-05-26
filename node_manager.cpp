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

int nodeArrayAdd(platyNode **nodeArray, unsigned char *mac_address, char *ip_address){
    unsigned char blankMAC[] = {0,0,0,0,0,0};
    for(int x=1; x<10; x++) {
        if(memcmp(blankMAC,nodeArray[x]->nodeMACAddress,6)==0) {
            memcpy(nodeArray[x]->nodeMACAddress,mac_address,6);
            memcpy(nodeArray[x]->nodeIPAddress,ip_address,INET_ADDRSTRLEN);
            return(x);
        }
    }
    return(-1); // no empty array elements
}

int nodeArrayCount(platyNode **nodeArray){
    int count=0;
    unsigned char blankMAC[] = {0,0,0,0,0,0};
    for(int x=0; x<10; x++) {
        if(memcmp(blankMAC,nodeArray[x]->nodeMACAddress,6)!=0){
            count++;
        }
    }
    return(count);
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

int nodePopulateSelf(platyNode **nodeArray)
{
    ifaddrs *addrs,*tmp;

    struct ifreq ifr;
    struct ifconf ifc;
    char buf[1024];
    int success = 0;

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
                    memcpy(nodeArray[0]->nodeIPAddress,inet_ntoa(pAddr->sin_addr),INET_ADDRSTRLEN);
                    struct sockaddr_in *pIfc = (struct sockaddr_in *)nodeArray[0]->nodeInterface.ifa_addr;
                    printf("Live Interface %s found - %s.\n",
                           nodeArray[0]->nodeInterface.ifa_name,
                           nodeArray[0]->nodeIPAddress);
                }
            }
        }

        tmp = tmp->ifa_next;
    }

freeifaddrs(addrs);

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) { /* handle error*/ };

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { /* handle error */ }

    struct ifreq* it = ifc.ifc_req;
    const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

    for (; it != end; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    success = 1;
                    break;
                }
            }
        }
        else { /* handle error */ }
    }

    unsigned char mac_address[6];

    if (success) memcpy(nodeArray[0]->nodeMACAddress, ifr.ifr_hwaddr.sa_data, 6);
    for(int x=0;x<6;x++){
        printf("%02X ",nodeArray[0]->nodeMACAddress[x]);
    }
        printf("\n");
}

int nodeCheckHaveAddress(platyNode **nodeArray, unsigned char *mac_address)
{
    for(int x=0; x<10; x++){
        if(memcmp(nodeArray[x]->nodeMACAddress,mac_address,6)==0){
            return(x);
        }
    }
    return(-1);
}
