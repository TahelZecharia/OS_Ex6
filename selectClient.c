/*
** selectClient.c -- a stream socket client demo
We took the customer's code from the link attached to the task.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 
int sockfd;


void *client_recive(void *arg){
    int len = 0;
    char data[1024] = {0};
    while ((len = recv(sockfd, data, 1024, 0)) != -1){
        if (!len){
            break;
        }
        printf("\nmsg get: %s\n",data);
        bzero(data, sizeof(data));
    }
    return NULL;
}


void *client_send(void *arg){
    char data[1024] = {0};
    while (1){    
        
        printf("enter msg: ");
        
        scanf("%s",data);
        
        if (send(sockfd, data, strlen(data), 0) == -1){
            perror("send");
        }
        
        bzero(data, sizeof(data));
    }
    return NULL;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[]){

    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    
    printf("connecting to %s\n", s);
    freeaddrinfo(servinfo); // all done with this structure

    pthread_t thread[2];
   
    pthread_create(&thread[0], NULL, client_recive, NULL);
    pthread_create(&thread[1], NULL, client_send, NULL);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    close(sockfd);

    return 0;
}