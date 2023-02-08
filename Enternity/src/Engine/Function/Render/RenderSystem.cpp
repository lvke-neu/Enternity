#include "RenderSystem.h"
#include "../../Core/Log/Log.h"
#include <glad/glad.h>

namespace Enternity
{
	void RenderSystem::initialize()
	{
		LOG_INFO("RenderSystem initialization");
	}

	void RenderSystem::uninitialize()
	{
		LOG_INFO("RenderSystem uninitialization");
	}

	void RenderSystem::clear(const Vector4f& vec4)
	{
		glClearColor(vec4.x, vec4.y, vec4.z, vec4.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}