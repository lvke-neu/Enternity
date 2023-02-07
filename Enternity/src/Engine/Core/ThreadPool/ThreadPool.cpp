#include "ThreadPool.h"
#include "../Basic/Macro.h"
#include "../Log/Log.h"

namespace Enternity
{

	ThreadPool::ThreadPool() : m_threadNum(1)
	{

	}

	ThreadPool::ThreadPool(unsigned int threadNum) : m_threadNum(threadNum)
	{

	}

	void ThreadPool::start()
	{
		ENTERNITY_ASSERT(m_threads.empty());
		for (unsigned int i = 0; i < m_threadNum; ++i)
		{
			m_threads.emplace_back(std::thread(&ThreadPool::work, this));
		}
		for (unsigned int i = 0; i < m_threadNum; ++i)
		{
			m_threads[i].detach();
		}
	}

	void ThreadPool::work()
	{
		while (true)
		{
			ITask* task = nullptr;

			m_mtxTaskQueue.lock();
			if (!m_taskQueue.empty())
			{
				task = m_taskQueue.front();
				m_taskQueue.pop();
			}
			m_mtxTaskQueue.unlock();

			if (task)
				task->Run();
		}
	}

	void ThreadPool::assign(ITask* task)
	{
		m_mtxTaskQueue.lock();
		m_taskQueue.push(task);
		m_mtxTaskQueue.unlock();
	}

}