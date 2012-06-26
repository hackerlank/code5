#ifndef _CON_LOCK_H
#define _CON_LOCK_H

#include <assert.h>

class Lock {
public:
	void lock(){};
	void unlock(){};

	bool trylock(){
		assert(false);
		return false;
	};
};

#endif
