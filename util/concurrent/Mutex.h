#ifndef _CON_MUTEX_H
#define _CON_MUTEX_H

#include "Lock.h"
#include <pthread.h>

class Mutex : public Lock {
public:
	Mutex(){
		pthread_mutex_init(&_mutex, NULL);
	}

	~Mutex() {
		pthread_mutex_destroy(&_mutex);
	}

	void lock() {
		pthread_mutex_lock(&_mutex);
	}

	void unlock() {
		pthread_mutex_unlock(&_mutex);
	}

	bool trylock() {
		return 0 == pthread_mutex_trylock(&_mutex);
	}

private:
	pthread_mutex_t _mutex;
};

#endif
