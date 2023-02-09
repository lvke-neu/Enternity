#pragma once
#include <chrono>
#include "Engine/Core/Log/Log.h"

namespace Enternity
{
	class ExecutionTimer
	{
	public:
		ExecutionTimer(const char* desc) : m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::steady_clock::now();
			m_executionDesc = desc;
		}

		~ExecutionTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();
			m_Stopped = true;

			LOG_INFO("{0}:Execution Time = {1}ms", m_executionDesc, elapsedTime.count()/1000);
		}
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
		const char* m_executionDesc = "";
	};
}

