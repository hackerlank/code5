#ifndef _CON_SCOPELOCK_H
#define _CON_SCOPELOCK_H

#include "Lock.h"

class ScopeLock {
public:
	ScopeLock(Lock& lock)
		:_lock(lock)
	{
		lock.lock();
	}

	~ScopeLock() {
		_lock.unlock();
	}

private:
	Lock& _lock;
};
#endif
