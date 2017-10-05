//
// Created by gilinsky on 10/5/17.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <cerrno>
#include <thread>
#include <netdb.h>
#include <signal.h>
#include <wait.h>
#include <arpa/inet.h>

#include "tcp_listener.h"

using namespace std;


void connection_handler(int fd, char address[INET6_ADDRSTRLEN])
{
    int read_size;
    char client_message[2000];

    while((read_size=recv(fd,client_message,2000,0))>0)
    {
        //echo the message back to the client
        write(fd,client_message,strlen(client_message));
    }
    if(read_size==0){
        printf("%s disconnected.\n",address);

        close(fd);
        exit(0);
    }
    else if(read_size==-1){
        perror("recv failed");
        close(fd);
        exit(0);
    }

}
void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int tcp_listener(void)
{
    int sockfd, new_fd, read_size;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    char client_message[2000];
    int rv;


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, tcp_listener_port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }
    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, tcp_listener_backlog) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener


            thread connection(connection_handler,new_fd,s);
            connection.detach();

            while(1){

            }
/*            while((read_size=recv(new_fd,client_message,2000,0))>0)
            {
                //echo the message back to the client
                write(new_fd,client_message,strlen(client_message));
            }
            if(read_size==0){
                printf("%s disconnected.\n",s);

                close(new_fd);
                exit(0);
            }
            else if(read_size==-1){
                perror("recv failed");
                close(new_fd);
                exit(0);
            }
            */

        }
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}


