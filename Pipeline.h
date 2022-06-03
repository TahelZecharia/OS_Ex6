
# pragma once

#include "ActiveObject.h"

void enSecond(void* node);
void enThird(void* node);

Queue* q1;
Queue* q2;
Queue* q3;


// Pipline
typedef struct _Pipeline {

    AO *first;
    AO *second;
    AO *third;

} Pipeline;

// Create a new Pipeline:
Pipeline* createPipeline(Queue* q1, Queue* q2, Queue* q3, void (*firstFunc)(void *), void (*secondFunc)(void *), void (*thirdFunc)(void *)){

    printf("***  create Pipline func  ***\n");

    Pipeline* pipe = (Pipeline*)(malloc(sizeof(Pipeline)));

    pipe->first = newAO(q1, firstFunc, enSecond);
    pipe->second = newAO(q2, secondFunc, enThird);
    pipe->third = newAO(q3, thirdFunc, deleteNode);

    return pipe;
}

void destroyPipeline(Pipeline* pipe){

    printf("***  destroy Pipeline func  ***\n");

    destroyAO(pipe->first);
    destroyAO(pipe->second);
    destroyAO(pipe->third);

    free(pipe);

}

void enSecond(void* node){

    printf("***  Second Pipline func  ***\n");

    enQ(q2, node);
}

void enThird(void* node){

    printf("***  Third Pipline func  ***\n");

    enQ(q3, node);
}


