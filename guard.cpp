#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//clang++-9 -p_thread Guard.cpp
//Such a guard can be used to protect strtok
class guard {
public:
    guard() {
        pthread_mutex_lock(&lock);
        cout<<"--Constractor guard--"<<endl;
    }

    ~guard() {
        pthread_mutex_unlock(&lock);
        cout<<"--Destractor guard--"<<endl;
    }

};

void* using_guard(void* x){
    guard g;
    sleep(3);
    return NULL;
}

int main(){
    pthread_t th1;
    pthread_t th2;
    static int a = 1;


    pthread_create(&th1, NULL, &using_guard, &a);
    pthread_create(&th2, NULL, &using_guard, &a);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
}
