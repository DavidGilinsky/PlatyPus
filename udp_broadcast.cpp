//
// Created by gilinsky on 11/23/17.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <sys/time.h> /* select() */

//for Mac OS X
#include <stdlib.h>

#define REMOTE_SERVER_PORT 1500
#define MAX_MSG 100


#include "udp_broadcast.h"
#include "node_manager.h"

int udp_broadcast(platyNode **nodeArray) {

  int sd, rc, i;
  struct sockaddr_in cliAddr, remoteServAddr;
  struct hostent *h;
  int broadcast = 1;
    char outputBuffer[14];


  /* get server IP address (no check if input is IP address or DNS name */
  h = gethostbyname("255.255.255.255");
  if(h==NULL) {
    printf("%s: unknown host '%s' \n", "255.255.255.255");
    exit(1);
  }

  printf("udp_broadcast: sending data to '%s' (IP : %s) \n",  h->h_name,
         inet_ntoa(*(struct in_addr *)h->h_addr_list[0]));

  remoteServAddr.sin_family = h->h_addrtype;
  memcpy((char *) &remoteServAddr.sin_addr.s_addr,
         h->h_addr_list[0], h->h_length);
  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);

  /* socket creation */
  sd = socket(AF_INET,SOCK_DGRAM,0);
  if(sd<0) {
    printf("udp_broadcast: cannot open socket \n");
    exit(1);
  }

 if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast,sizeof broadcast) == -1) {
          perror("setsockopt (SO_BROADCAST)");
          exit(1);
  }

  /* bind any port */
  cliAddr.sin_family = AF_INET;
  cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  cliAddr.sin_port = htons(0);

  rc = bind(sd, (struct sockaddr *) &cliAddr, sizeof(cliAddr));
  if(rc<0) {
    printf("udp_ broadcast: cannot bind port\n");
    exit(1);
  }

    /* build output buffer */

    memcpy(outputBuffer,"PlatyPus",8);
    memcpy(outputBuffer+8,nodeArray[0]->nodeMACAddress,6);
  /* send data */

    rc = sendto(sd, outputBuffer, strlen(outputBuffer)+1, 0,
                (struct sockaddr *) &remoteServAddr,
                sizeof(remoteServAddr));

    if(rc<0) {
      printf("udp_broadcast: cannot send data %d \n",i-1);
      close(sd);
      exit(1);
    }


  return 1;

}


