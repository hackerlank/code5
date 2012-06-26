#ifndef _ISCHEDULER_H
#define _ISCHEDULER_H

#include <boost/function.hpp>
#include "util/Timer.h"

using boost::function1;

class IScheduler;

class ISchedFeture{
public:
	ISchedFeture(IScheduler* sheduler)
		:m_done(false), m_scheduler(m_scheduler)
	{}
	virtual void run(long elapsed) = 0;
	
	void cancel() {
		//if (!m_done)
		//	m_scheduler->cancel(this);
	}

	bool isDone() {
		return m_done;
	}

	void setDone(bool b) {
		m_done = b;
	}
protected:
	bool m_done;
	IScheduler* m_scheduler;
};

typedef function1<void, long> SchedFunc;
class IScheduler {
public:
	virtual void update(long elapsed) = 0;	//ms
	virtual ISchedFeture* schedule(SchedFunc func, long time, TimeUnit unit) = 0;
	virtual ISchedFeture* schedulePeroid(SchedFunc func, long period, long firstDelay, TimeUnit unit) = 0;

	virtual void cancel(ISchedFeture* feture) = 0;
};

#endif
