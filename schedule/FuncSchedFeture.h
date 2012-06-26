#pragma once

#include "IScheduler.h"

class FuncSchedFeture : public ISchedFeture{
public:
	FuncSchedFeture(SchedFunc f, IScheduler* sched)
		:ISchedFeture(sched), m_function(f)
	{}

	void run(long elapsed)
	{
		m_function(elapsed);
	}

private:
	SchedFunc m_function;
};