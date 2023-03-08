#include "ThreadPool.h"

namespace Enternity
{
	void ThreadPool::initialize(int threadCount)
	{
		createThreadPool(threadCount);
	}

	void ThreadPool::uninitialize()
	{
		m_stoped.store(true);
		m_cv.notify_all();
		for (std::thread& thread : m_threadPool)
		{
			if (thread.joinable())
				thread.join();
		}
	}

	void ThreadPool::createThreadPool(int threadCount)
	{
		threadCount = threadCount < 1 ? 1 : threadCount;
		for (int i = 0; i < threadCount; i++)
		{
			m_threadPool.emplace_back(
				[this]() {
					while (!this->m_stoped)
					{
						std::function<void()> task;
						{
							std::unique_lock<std::mutex> lock{ this->m_lock };
							this->m_cv.wait(lock, [this]() {return this->m_stoped.load() || !this->m_tasks.empty(); });
							if (this->m_stoped && this->m_tasks.empty())
								return;
							task = std::move(this->m_tasks.front());
							this->m_tasks.pop();
						}
						task();
						m_undo--;
					}
				}
			);
		}
	}

	void ThreadPool::commitTask(const std::function<void()>& task)
	{
		if (m_stoped.load())
			return;
		std::lock_guard<std::mutex> lock{ m_lock };
		m_tasks.push(task);
		m_undo++;
		m_cv.notify_one();
	}

	bool ThreadPool::finished()
	{
		return m_undo == 0;
	}
}

