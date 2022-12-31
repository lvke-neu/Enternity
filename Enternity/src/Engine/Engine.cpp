#include "Engine.h"

BEGIN_ENTERNITY

void Engine::Initialize()
{
	m_timer.Reset();
	m_timer.Start();
}

void Engine::Tick()
{
	m_timer.Tick();
}

float Engine::GetFps()
{
	return m_timer.getFps();
}

END_ENTERNITY