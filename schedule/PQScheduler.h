#ifndef _PQSCHEDULER_H
#define _PQSCHEDULER_H

#include "IScheduler.h"
#include "FuncSchedFeture.h"
#include <boost/tuple/tuple.hpp>
#include <boost/function.hpp>
//#include <boost/heap/priority_queue.hpp>
#include <queue>

using boost::function;
using boost::tuple;
using boost::make_tuple;
using std::priority_queue;

class PQScheduler : public IScheduler {
public:
	typedef tuple<long, ISchedFeture*> ElemType;
public:
	PQScheduler(int resolution);
	
	void update(long elapsed); //ms
	
	ISchedFeture* schedule(SchedFunc func, long time, TimeUnit unit);
	ISchedFeture* schedulePeroid(SchedFunc func, long period, long firstDelay, TimeUnit unit){ return 0;};

	void cancel(ISchedFeture* feture);
private:
	priority_queue<ElemType> m_plans;
	long m_elapsed;
	long _elapsedAcc;

	const long _resolution;
};

#endif