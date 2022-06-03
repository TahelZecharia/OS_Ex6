#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


typedef void *(*pfunc)(void *arg);

typedef struct Reactor
{
    int id_file;
    pthread_t thread;
    pfunc function;
} _reactor, *Preactor;

typedef struct _reqests
{
    int id_file;
    Preactor reactor;
} _reqests, *Preqests;

Preactor newReactor(){
    Preactor reactor = (Preactor)(malloc(sizeof(_reactor)));
    return reactor;
}

void InstallHandler(Preactor reactor, pfunc func, int id){
    reactor->function = func;
    reactor->id_file = id;
    Preqests req = (Preqests)(malloc(sizeof(_reqests)));
    req->id_file = id;
    req->reactor = reactor;
    pthread_create(&reactor->thread, NULL, func, req);
}

void RemoveHandler(Preactor reactor, int fd){
    pthread_join(reactor->thread, NULL);
    reactor->id_file = -1;
    reactor->function = NULL;
}
