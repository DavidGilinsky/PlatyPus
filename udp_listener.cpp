//
// Created by gilinsky on 11/23/17.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */

//for Mac OS X
#include <stdlib.h>


#include "udp_listener.h"
#include "node_manager.h"

#define LOCAL_SERVER_PORT 1500
#define MAX_MSG 100

using namespace std;

int udp_listener(platyNode **nodeArray) {

  int sd, rc, n;
  socklen_t cliLen;
  struct sockaddr_in cliAddr, servAddr;
  char msg[MAX_MSG];
  int broadcast = 1;

  printf("Creating udp listener socket\n");

  /* socket creation */
  sd=socket(AF_INET, SOCK_DGRAM, 0);
  if(sd<0) {
    printf("UDP listener cannot open socket \n");
    exit(1);
  }

  printf("Setting udp listener socket options.\n");

  if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast,sizeof broadcast) == -1) {
          perror("setsockopt (SO_BROADCAST)");
          exit(1);
  }


  printf("Binding udp listener to port %d.\n",LOCAL_SERVER_PORT);

  /* bind local server port */
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr));
  if(rc<0) {
    printf("UDP listener cannot bind port number %u \n",
           LOCAL_SERVER_PORT);
    exit(1);
  }

  printf("waiting for data on port UDP %u\n",
           LOCAL_SERVER_PORT);


  /* server infinite loop */

  while(1) {
          /* init buffer */
    memset(msg,0x0,MAX_MSG);


    /* receive message */
    cliLen = sizeof(cliAddr);
    n = recvfrom(sd, msg, MAX_MSG, 0,
                 (struct sockaddr *) &cliAddr, &cliLen);

    if(n<0) {
      printf("cannot receive data \n");
      continue;
    }

    if(strstr(msg,"PlatyPus")!=NULL){
      printf("Found PlatyPus Node at %s\n",inet_ntoa(cliAddr.sin_addr));
      struct sockaddr_in *pIfc = (struct sockaddr_in *)nodeArray[0]->nodeInterface.ifa_addr;
      if(cliAddr.sin_addr.s_addr==pIfc->sin_addr.s_addr) {
        printf("oh wait... that's me!\n");
      }
    }

    /* print received message */
    printf("from %s:UDP%u : %s \n",
           inet_ntoa(cliAddr.sin_addr),
           ntohs(cliAddr.sin_port),msg);



  }
/* end of server infinite loop */


return 0;

}


