#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <mutex>
#include <sys/mman.h>
#include <chrono>
#include <future>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
pthread_mutex_t _mutex;

// we use implement from here: http://enki-tech.blogspot.com/2012/08/c11-generic-singleton.html

template<typename T>
class Singleton
{
private:

	static Singleton* m_instance;

	Singleton(Singleton* temp){
         m_instance = temp; 
    };

public:
	static Singleton* Instance(Singleton<T> *temp);
	static void Destroy();


};

template<typename T>
Singleton<T> *Singleton<T>::m_instance = 0;

template<typename T>
Singleton<T> *Singleton<T>::Instance(Singleton<T> *temp){
	if(!m_instance)
	{
        pthread_mutex_lock(&_mutex);
        m_instance = new Singleton(temp);
        pthread_mutex_unlock(&_mutex);
		
	}

	return m_instance;
}

template<typename T>
void Singleton<T>::Destroy()
{
	delete (m_instance);
	m_instance = 0;
}



int main(){

    int file_fd = open("stav.txt", O_RDONLY);
    Singleton<int*>* map =(Singleton<int*>*) mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, file_fd, 0);
    Singleton<int*>* f1=Singleton<int*>::Instance(map);
    Singleton<int*>*f2=Singleton<int*>::Instance(map);
    if (f1 == f2){
        cout<<"--------GOOD!--------"<<endl;
        cout << "The singleton works - only one succeeded to build an object and the other failed" << endl;
    }
    else{cout<<"-------- NOT GOOD!--------"<<endl;
        cout << "The singelton failed" << endl;
    }
}