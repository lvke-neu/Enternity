#include "Engine/Core/Log/Log.h"

int main()
{
	Enternity::Log::Init();
	LOG_TRACE("asbdsa{0}{1}", 1,"dsad");
	LOG_INFO("asbdsa%d%s", 1, "dsds");
	LOG_WARN("asbdsa%d%s", 1, "dsds");
	LOG_ERROR("asbdsa%d%s", 1, "dsds");
	LOG_CRITICAL("asbdsa%d%s", 1, "dsds");
	while (true);
	return 0;
}