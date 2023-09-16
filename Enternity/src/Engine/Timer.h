//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#ifndef GAMETIMER_H
#define GAMETIMER_H

namespace Enternity
{
	class Timer
	{
	public:
		Timer();

		float totalTime()const;
		//the unit is second
		inline float* deltaTime()
		{
			return &m_deltaTime;
		}

		void reset();
		void start();
		void stop();
		void tick();

	private:
		double m_secondsPerCount;
		float m_deltaTime;

		__int64 m_baseTime;
		__int64 m_pausedTime;
		__int64 m_stopTime;
		__int64 m_prevTime;
		__int64 m_currTime;

		bool m_stopped;
	};
}
#endif // GAMETIMER_H