#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <queue>
#include <functional>
#include "Core/Basic/Macro.h"

namespace Enternity
{
	class ThreadPool
	{
		PRIVATE(ThreadPool);
		SINGLETON(ThreadPool);
	public:
		void initialize(int threadCount);
		void uninitialize();
	private:
		void createThreadPool(int threadCount);
	public:
		void commitTask(const std::function<void()>& task);
		bool finished();
	private:
		using Task = std::function<void()>;
	
		std::vector<std::thread> m_threadPool;
		
		std::queue<Task> m_tasks;
	
		std::mutex m_lock;
	
		std::condition_variable m_cv;
		
		std::atomic<bool> m_stoped{ false };
		
		std::atomic<int> m_undo{ 0 };
	};
}