
# pragma once 

#include <pthread.h>
#include <ctype.h>
#include "Queue.h"

// Active Object:
typedef struct ActiveObject {
    
    Queue *queue;
    void (*firstFunc)(void *);
    void (*secondFunc)(void *);
    pthread_t* thread;
    int flag;

} AO;

AO* newAO(Queue *queue, void (*firstFunc)(void *), void (*secondFunc)(void *));
void* threadAO(void* activeObject);
void destroyAO(AO* activeObject);
void aAbB(void* p);
void keysar(void* p);


// Create a new Active Object:
AO* newAO(Queue *queue, void (*firstFunc)(void *), void (*secondFunc)(void *)){

    printf("***  new AO func  ***\n");

   AO* activeObject = (AO*)malloc(sizeof(AO));
   activeObject->flag = 0;
   activeObject->queue = queue;
   activeObject->firstFunc = firstFunc;
   activeObject->secondFunc = secondFunc;
   activeObject->thread = (pthread_t*)malloc(sizeof(pthread_t));
   pthread_create((activeObject->thread), NULL, threadAO, (void*)activeObject);
   return activeObject;
}

// Main loop:
void* threadAO(void* activeObject){

    printf("***  thread AO func  ***\n");

    AO* active = (AO*)activeObject;

    active->flag = 1;

    while(active->flag == 1){

        Node* temp = (Node*)deQ(active->queue);
        active->firstFunc(temp);
        active->secondFunc(temp);
    }
}

// Delete an Active Object:
void destroyAO(AO* activeObject) {

    printf("***  destroy AO func  ***\n");

    activeObject->flag = 0;
    destroyQ(activeObject->queue);
    free(activeObject);
}

void aAbB(void* p){

    printf("***  aAbB func  ***\n");

    Node *temp = (Node*) p;

    int len = strlen(temp->data);
    
    for(int i =0; i<len; i++){

        if(temp->data[i]>='a' && temp->data[i]<='z'){

            temp->data[i] = temp->data[i] - 'a' + 'A';
        }
        else if(temp->data[i]>='A' &&temp->data[i]<='Z'){

            temp->data[i] = temp->data[i] - 'A' + 'a';
        }
    }
}

void keysar(void* p){

    printf("***  keysar func  ***\n");
    
    Node *temp = (Node*) p;

    int len = strlen(temp->data);

    for(int i =0; i<len; i++){

        if (temp->data[i] == 'Z') {

            temp->data[i] = 'A';
        } 

        else if (temp->data[i] == 'z') {

            temp->data[i] = 'a';
        }
        
        else {

            temp->data[i] += 1;
        }
    }
}

