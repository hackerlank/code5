#ifndef _CON_RWLOCK_H
#define _CON_RWLOCK_H

#include <pthread.h>

class RWLock {
public:
	RWLock() {
		pthread_rwlock_init(&_lock, NULL);
	}

	~RWLock() {
		pthread_rwlock_destroy(&_lock);
	}

	void rlock() {
		pthread_rwlock_rdlock(&_lock);
	}

	bool rtrylock() {
		return 0 == pthread_rwlock_tryrdlock(&_lock);
	}

	void wlock() {
		pthread_rwlock_wrlock(&_lock);
	}

	bool wtrylock() {
		return 0 == pthread_rwlock_trywrlock(&_lock);
	}

	void unlock() {
		pthread_rwlock_unlock(&_lock);
	}

private:
	pthread_rwlock_t _lock;
};

#endif
