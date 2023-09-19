#pragma once
#include <functional>

namespace Enternity
{
	class Command
	{
	public:
		Command(const std::function<void()>& command);
		void execute();
	private:
		std::function<void()> m_command;
	};
}