#include <iostream>
#include "Window/OpenglWindow.h"
#include "Log/Log.h"

int main()
{
	LOG_INFO("startr");
	LOG_DEBUG("startr");
	LOG_WARN("startr");
	LOG_ERROR("startr");


	Enternity::OpenglWindow openglWindow({ 1024, 764, "hello, opengl" });
	if (openglWindow.Initialize())
	{
		openglWindow.Run();
	}

	return 0;
}