#include "Thread.h"

void* Thread::_thread_routine(void* t) {
	Thread* th = (Thread*)t;
	th->_state = TSRunning;
	th->run();
	th->_state = TSTerminated;

	return NULL;
}

Thread::Thread()
	:_state(TSCreate)
{
}

int Thread::start()
{
	int ret = pthread_create(&_thid, NULL, _thread_routine, (void*)this);
	return ret;
}

void Thread::exit()
{
	pthread_exit(&_thid);
}

int Thread::join(Thread* th)
{
	if (!th)
		return 0;

	return pthread_join(th->_thid, NULL);
}
