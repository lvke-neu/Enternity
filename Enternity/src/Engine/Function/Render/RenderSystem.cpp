#include "RenderSystem.h"
#include "Core/Math/Vector4.h"
#include "Core/Log/Log.h"
#include "Function/Scene/Scene.h"
#include "Function/Scene/Camera3D.h"
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
		const auto& view = scene->m_registry.view<MaterialComponent, ShaderComponent, MeshComponent>();
		for (auto& entity : view)
		{
			auto [matc,shaderc,meshc] = view.get<MaterialComponent, ShaderComponent, MeshComponent>(entity);
			if (shaderc.m_shader)
			{
				shaderc.m_shader->bind();
				Matrix4x4f vp = scene->m_camera3D->getProjMatrix() * scene->m_camera3D->getViewMatrix();
				shaderc.m_shader->setMat4("vp", vp, true);
			}

			if (matc.m_texture2D)
			{
			}

			if (meshc.m_vertexArray && meshc.m_vertexbuffer && meshc.m_indexbuffer)
			{
				meshc.m_vertexArray->bind();
				meshc.m_indexbuffer->bind();
				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshc.m_indexbuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
			}
		}
	}
}