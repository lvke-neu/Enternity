#include "RenderSystem.h"
#include "Core/Math/Vector4.h"
#include "Core/Log/Log.h"
#include "Function/Scene/Scene.h"
#include "Function/Scene/ECS/Component/MeshRenderComponents.hpp"
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

	void RenderSystem::setViewPort(unsigned int width, unsigned int height)
	{
		glViewport(0, 0, width, height);
	}

	void RenderSystem::clear(const Vector4f& vec4)
	{
		CHECK_GL_CALL(glClearColor(vec4.x, vec4.y, vec4.z, vec4.w));
		CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)));
	}

	void RenderSystem::drawCall(Scene* scene)
	{
		m_drawcalls.push(scene);
	}

	void RenderSystem::tick()
	{
		clear(Vector4f::DARK_COLOR);
		while (!m_drawcalls.empty())
		{
			Scene* scene = m_drawcalls.front();
			m_drawcalls.pop();
			if (scene)
				drawScene(scene);
		}
	}

	void RenderSystem::drawScene(Scene* scene)
	{
		for (auto& entity : scene->m_entities)
		{
			auto& comp = entity.second.getComponent<ShaderComponent>();
			if (comp.m_shader)
			{
				static int index = 0;
				if (index++ == 0)
				{
					LOG_TRACE("shader load finished");
				}
			}

			auto& comp2 = entity.second.getComponent<MaterialComponent>();
			if (comp2.m_texture2D)
			{
				static int index2 = 0;
				if (index2++ == 0)
				{
					LOG_TRACE("texture load finished");
				}
			}
		}
	}
}