/*
We used the code at the following link:
https://drive.google.com/drive/folders/11bVv3fuFjPXy071tFwS7pHaGqbzB7V4-
*/

# pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// pthread_mutex_t lock;
// pthread_cond_t cond;

// Node:
typedef struct _Node {

	struct _Node* next;
	char data[250];
   int sock;

} Node;

// Queue:
typedef struct _Queue {

    int size;
    Node *head;
    Node *tail;
    pthread_mutex_t lock;
    pthread_cond_t cond; 
   
} Queue;


Queue* createQ();
void destroyQ(Queue* q);
void* deQ(Queue* q);
void enQ(Queue* q, void* data);

// Create a new Node:
Node* newNode(char* data, int sock){

   printf("***  new Node func  ***\n");

    Node* node = (Node*)malloc(sizeof(Node)); 
    
    strcpy(node->data, data);
    node->data[strlen(data)] = '\0';
    node->sock = sock;
    node->next = NULL;

    return node;
}

// Delete a Node:
void deleteNode(void* node){

   printf("***  delete Node func  ***\n");

    if(node == NULL){

        return;
    }

    free((Node*)node);
}

// Create a new queue:
Queue* createQ() {

   printf("***  create Queue func  ***\n");

   Queue* q = (Queue*)malloc(sizeof(Queue));

   q->head = q->tail = NULL;
   q->size = 0;

   pthread_mutex_init(&q->lock, NULL);
   pthread_cond_init(&q->cond, NULL);
   
   return q;
}

// Delete an existing queue:
void destroyQ(Queue* q) {

   printf("***  destroy Queue func  ***\n");

   if(q == NULL)
      return;

   while(deQ(q) != NULL);
      
   free(q);
}

// Insert a new Node into the queue:
void enQ(Queue* q, void* node) {

   printf("***  insert Queue func  ***\n");

   pthread_mutex_lock(&(q->lock));
 
   if(q->tail == NULL) {

      q->head = q->tail = (Node*)node;

      q->size++; 

      pthread_mutex_unlock(&(q->lock)); 

      pthread_cond_signal(&(q->cond));
   }

   else {

      q->tail->next = (Node*)node;
      q->tail = (Node*)node;
      q->size++; 
      pthread_mutex_unlock(&(q->lock)); 
   }
}

// Remove of the Node at the head of the queue:
void* deQ(Queue* q) {

   printf("***  remove Queue func  ***\n");

   pthread_mutex_lock(&(q->lock));

   Node* prev;
   void* data;
   
   if(q->head == NULL){

      pthread_cond_wait(&(q->cond), &(q->lock));
   }

   prev = q->head;

   if(prev == NULL){

      pthread_exit(NULL);
      // return NULL;
   }
 
   q->head = q->head->next;
   
   if (q->head == NULL)

      q->tail = NULL;

   q->size--;

   pthread_mutex_unlock(&(q->lock));

   return prev;
}

void sendNode(void *node){

   printf("***  send Node func  ***\n");

   if (node == NULL) {
      
      return;
   }
   
   Node* temp = (Node*)node;

   if (send(temp->sock, (temp->data), strlen(temp->data), 0) == -1){
      
      perror("send");
   }

}




