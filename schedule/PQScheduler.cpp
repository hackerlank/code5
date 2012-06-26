#include "PQScheduler.h"
#include "FuncSchedFeture.h"
#include "util/Timer.h"

bool operator<(const PQScheduler::ElemType& a, const PQScheduler::ElemType& b)
{
	return a.get<0>() > b.get<0>();
}

PQScheduler::PQScheduler(int resolution)
	:m_elapsed(0L), _elapsedAcc(0), _resolution(resolution)
{
}

void PQScheduler::update(long elapsed)
{
	m_elapsed += elapsed;

	_elapsedAcc += elapsed;
	if (elapsed <= _resolution || m_plans.empty())
		return;

	_elapsedAcc -= _resolution;

	ElemType top = m_plans.top();
	while (top.get<0>() < m_elapsed) {
		m_plans.pop();
		
		ISchedFeture* feture = top.get<1>();
		feture->run( 0 );
		feture->setDone(true);

		if (m_plans.empty())
			break;

		top = m_plans.top();
	}
}

ISchedFeture* PQScheduler::schedule(SchedFunc func, long time, TimeUnit unit)
{
	ISchedFeture* feture = new FuncSchedFeture(func, this);
	m_plans.push(make_tuple(timeToMs(time, unit) + m_elapsed, feture));
	return feture;
}

void PQScheduler::cancel(ISchedFeture* feture)
{
	//m_plans.erase(
}
