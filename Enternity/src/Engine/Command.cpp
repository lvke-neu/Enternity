#include "Command.h"

namespace Enternity
{
	Command::Command(const std::function<void()>& command) :
		m_command(command)
	{

	}

	void Command::execute()
	{
		m_command();
	}
}