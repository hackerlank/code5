#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>

enum ThreadState {
	TSCreate,
	TSRunning,
	TSTerminated
};

class Thread {
public:
	static void* _thread_routine(void*);

public:
	Thread();
	virtual ~Thread(){}
	virtual void run() = 0;

	int start();
	void exit();

	int join(Thread* th);

	ThreadState state();
private:
	ThreadState _state;
	pthread_t	_thid;
};
#endif
