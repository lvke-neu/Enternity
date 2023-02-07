/***************************************************************************************
Author: lvke
Date:2023/2/7 22:06
Description:
Engine
****************************************************************************************/
#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <mutex>

namespace Enternity
{
	class ITask
	{
	public:
		ITask() = default;
		virtual ~ITask() = default;
		
		virtual void Run() = 0;
	};

	class ThreadPool
	{
	public:
		ThreadPool();
		ThreadPool(unsigned int m_threadNum);
		
		void start();
		void work();
		void assign(ITask* task);
	private:
		unsigned int m_threadNum;
		std::mutex m_mtxTaskQueue;

		std::vector<std::thread> m_threads;
		std::queue<ITask*> m_taskQueue;
	};
}