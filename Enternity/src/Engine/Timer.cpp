//***************************************************************************************
// GameTimer.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include <windows.h>
#include "Timer.h"


namespace Enternity
{
	Timer::Timer()
		: m_secondsPerCount(0.0), m_deltaTime(-1.0), m_baseTime(0), m_stopTime(0),
		m_pausedTime(0), m_prevTime(0), m_currTime(0), m_stopped(false)
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_secondsPerCount = 1.0 / (double)countsPerSec;
	}

	// Returns the total time elapsed since Reset() was called, NOT counting any
	// time when the clock is stopped.
	float Timer::totalTime()const
	{
		// If we are stopped, do not count the time that has passed since we stopped.
		// Moreover, if we previously already had a pause, the distance 
		// m_StopTime - m_BaseTime includes paused time, which we do not want to count.
		// To correct this, we can subtract the paused time from m_StopTime:  
		//
		//                     |<--paused time-->|
		// ----*---------------*-----------------*------------*------------*------> time
		//  m_BaseTime       m_StopTime        startTime     m_StopTime    m_CurrTime

		if (m_stopped)
		{
			return (float)(((m_stopTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
		}

		// The distance m_CurrTime - m_BaseTime includes paused time,
		// which we do not want to count.  To correct this, we can subtract 
		// the paused time from m_CurrTime:  
		//
		//  (m_CurrTime - m_PausedTime) - m_BaseTime 
		//
		//                     |<--paused time-->|
		// ----*---------------*-----------------*------------*------> time
		//  m_BaseTime       m_StopTime        startTime     m_CurrTime

		else
		{
			return (float)(((m_currTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
		}
	}

	void Timer::reset()
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_baseTime = currTime;
		m_prevTime = currTime;
		m_stopTime = 0;
		m_pausedTime = 0;
		m_stopped = false;
	}

	void Timer::start()
	{
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


		// Accumulate the time elapsed between stop and start pairs.
		//
		//                     |<-------d------->|
		// ----*---------------*-----------------*------------> time
		//  m_BaseTime       m_StopTime        startTime     

		if (m_stopped)
		{
			m_pausedTime += (startTime - m_stopTime);

			m_prevTime = startTime;
			m_stopTime = 0;
			m_stopped = false;
		}
	}

	void Timer::stop()
	{
		if (!m_stopped)
		{
			__int64 currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			m_stopTime = currTime;
			m_stopped = true;
		}
	}

	void Timer::tick()
	{
		if (m_stopped)
		{
			m_deltaTime = 0.0;
			return;
		}

		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		m_currTime = currTime;

		// Time difference between this frame and the previous.
		m_deltaTime =float( (m_currTime - m_prevTime) * m_secondsPerCount);

		// Prepare for next frame.
		m_prevTime = m_currTime;

		if (m_deltaTime < 0.0)
		{
			m_deltaTime = 0.0;
		}
	}
}

