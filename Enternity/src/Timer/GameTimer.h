//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#ifndef GAMETIMER_H
#define GAMETIMER_H

class GameTimer
{
public:
	GameTimer();

	float TotalTime()const;		
	float DeltaTime()const;		

	void Reset();               
	void Start();               
	void Stop();                
	void Tick();  

	float getFps() { return m_fps; }
private:
	void calculateFps();
private:
	double m_SecondsPerCount;
	double m_DeltaTime;

	__int64 m_BaseTime;
	__int64 m_PausedTime;
	__int64 m_StopTime;
	__int64 m_PrevTime;
	__int64 m_CurrTime;

	bool m_Stopped;

	float m_fps = 0.0f;
};

#endif // GAMETIMER_H