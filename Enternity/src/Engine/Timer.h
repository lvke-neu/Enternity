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

		float TotalTime()const;
		//the unit is second
		inline float DeltaTime() const
		{
			return (float)m_DeltaTime;
		}

		void Reset();
		void Start();
		void Stop();
		void Tick();

	private:
		double m_SecondsPerCount;
		double m_DeltaTime;

		__int64 m_BaseTime;
		__int64 m_PausedTime;
		__int64 m_StopTime;
		__int64 m_PrevTime;
		__int64 m_CurrTime;

		bool m_Stopped;
	};
}
#endif // GAMETIMER_H