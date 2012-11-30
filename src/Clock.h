/**
 * by Zeying Peng, 2011-09-15
 */

#ifndef _Clock_h_
#define _Clock_h_

#include <ctime>

class Clock
{
public:
	Clock() : m_totalTimeElapsed(0) { m_last_clock = clock(); }
	~Clock() { }

	int millisecondElapsed()
	{
		clock_t tmp = m_last_clock;
		m_last_clock = clock();
		clock_t elapse_clock = m_last_clock - tmp;
		m_totalTimeElapsed += elapse_clock;

		return elapse_clock*1000 / CLOCKS_PER_SEC;
	}

	int totalMillisecondElapsed()
	{
		return m_totalTimeElapsed*1000 / CLOCKS_PER_SEC;
	}

private:
	clock_t m_last_clock;
	clock_t m_totalTimeElapsed;

};

#endif

