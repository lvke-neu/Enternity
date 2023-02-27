#include "RenderSystem.h"
#include "Core/Math/Vector4.h"
#include "Core/Event/WindowResizeEvent.h"
#include "Core/Event/EventManager.h"
#include "Function/Scene/Scene.h"
#include "Function/Scene/Camera/Camera3D.h"
#include "Function/Scene/ECS/Component/Visual3DComponent.h"
#include "Function/Scene/ECS/Component/TransformComponent.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include <glad/glad.h>

namespace Enternity
{
	void RenderSystem::initialize()
	{
		EventManager::GetInstance().registry(EventType::WindowResize, BIND_FUNC(RenderSystem::onResize));
		LOG_INFO("RenderSystem initialization");
	}

	void RenderSystem::uninitialize()
	{
		EventManager::GetInstance().unRegistry(EventType::WindowResize, BIND_FUNC(RenderSystem::onResize));
		LOG_INFO("RenderSystem uninitialization");
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
		//clear(Vector4f::DARK_COLOR);
		//while (!m_drawcalls.empty())
		//{
		//	Scene* scene = m_drawcalls.front();
		//	m_drawcalls.pop();
		//	if (scene)
		//		drawScene(scene);
		//}
	}

	void RenderSystem::drawScene(Scene* scene)
	{
		const auto& view = scene->m_registry.view<Visual3DComponent, TransformComponent>();
		for (auto& entity : view)
		{
			const auto& [v3dComp, transcomp] = view.get<Visual3DComponent, TransformComponent>(entity);
			if (v3dComp.m_rendererPassAssetImpl->getShader())
			{
				v3dComp.m_rendererPassAssetImpl->getShader()->bind();
				Matrix4x4f mvp = scene->m_camera3D->getProjMatrix() * scene->m_camera3D->getViewMatrix() * transcomp.getWorldMatrix();
				v3dComp.m_rendererPassAssetImpl->getShader()->setMat4("mvp", mvp, true);

				//render state
				if (v3dComp.m_rendererPassAssetImpl->getRenderState(RenderState::WireFrame))
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}

				if (v3dComp.m_rendererPassAssetImpl->getRenderState(RenderState::Depth))
				{
					glEnable(GL_DEPTH_TEST);
				}
				else
				{
					glDisable(GL_DEPTH_TEST);
				}
			}

			if (v3dComp.m_textureAssetImpl->getTexture2D())
			{
				int i = 0; i++;
			}

			auto& vertexArraies = v3dComp.m_MeshAssetImpl->getVertexArraies();
			auto& indexBuffers = v3dComp.m_MeshAssetImpl->getIndexBuffers();
			for (int i = 0; i < indexBuffers.size(); i++)
			{
				if (vertexArraies[i])
					vertexArraies[i]->bind();
				if (indexBuffers[i])
				{
					indexBuffers[i]->bind();
					CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));
				}
				
			}
	

			if (v3dComp.m_rendererPassAssetImpl->getShader())
			{
				v3dComp.m_rendererPassAssetImpl->getShader()->unbind();
			}

			if (v3dComp.m_textureAssetImpl->getTexture2D())
			{
			}

			for (int i = 0; i < indexBuffers.size(); i++)
			{
				if (vertexArraies[i])
					vertexArraies[i]->unbind();
				if (indexBuffers[i])
					indexBuffers[i]->unbind();
			}
		}
	}

	void RenderSystem::onResize(IEvent* event)
	{
		ENTERNITY_ASSERT(event != nullptr);

		CHECK_GL_CALL(glViewport(0, 0, ((WindowResizeEvent*)event)->getWidth(), ((WindowResizeEvent*)event)->getHeight()));
	}
}