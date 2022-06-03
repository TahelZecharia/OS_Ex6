
# Ex6 - OS COURSE

## Stav Zilber & Tahel Zecharia

## Our Project:

-In this task we implemented a synchronized multi-threaded queue, and several clients can connect to it in parallel. The queue is synchronized between the clients.
The commands we executed for the queue are:
1. createQ
2. destoryQ
3. enQ
4. deQ
(we implement this in main1.h)
  
-We then implemented an active object that receives a pointer to the function,
That you will read for each element in a queue and a function that you will read when the treatment ends.
That is, we built an active object pipeline.

-We also implemented guard and singleton classes.

-we implemented Reactor:
The reactor design pattern is an event handling pattern for handling service requests delivered concurrently to a service handler by one or more inputs.

## How to run our program:

  ----Open the terminal and write: make all----

  In order to run active object pipeline:

  1. In order to run the server, write: ./server

  2. In order to run the client, open a new terminal and write: ./client


  4. In order to run the guard, write: ./guard

  5. In order to run the singleton, write: ./singleton

  6. In order to run the Reactor:
    a. write: ./pollServer
    b. open a new terminal and write: ./selectClient


## Screenshot from our project of the server and three clients:

![WhatsApp Image 2022-06-03 at 17 41 21](https://user-images.githubusercontent.com/93916792/171878358-47090174-1a1b-439f-a1ef-9233408857d9.jpeg)

## Screenshot from our project of the server and three clients in the Reactor:

![Screenshot from 2022-06-03 17-38-46](https://user-images.githubusercontent.com/93916792/171878392-ae5f6a90-9c07-4bb1-af7b-7ef56079114c.png)


