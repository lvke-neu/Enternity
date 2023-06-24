#include "RenderSystem.h"
#include "Scene/Scene.h"
#include "RHI/FrameBuffer/FrameBuffer.h"
#include "RHI/Mesh/Mesh.h"
#include "RHI/Mesh/VertexArray.h"
#include "RHI/Mesh/IndexBuffer.h"
#include "RHI/Renderer/Renderer.h"
#include "RHI/Texture/Texture.h"
#include "RHI/Texture/TextureAsset.h"
#include "Engine/Engine.h"
#include "Engine/Event/EventSystem.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/Visual3DComponent.h"
#include <glad/glad.h>

namespace Enternity
{
	//TODO: move to class Scene
	static Texture* defaultTexture =nullptr;
	
	RenderSystem::RenderSystem()
	{
		m_frameBuffer1 = new FrameBuffer;
		Engine::GetInstance().getEventSystem()->registerEvent(EventType::WindowResize, BIND(RenderSystem::onWindowResize));				
	
		//TODO: move to class Scene
		TextureAsset ta("assets/textures/white_background.jpeg");
		ta.load(0);
		defaultTexture = new Texture(&ta);
	
	}

	RenderSystem::~RenderSystem()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(EventType::WindowResize, BIND(RenderSystem::onWindowResize));
		SAFE_DELETE_SET_NULL(m_frameBuffer1);
		SAFE_DELETE_SET_NULL(defaultTexture);
	}

	void RenderSystem::render(Scene* scene)
	{

		render_path_1(scene);

	}

	bool RenderSystem::cull(Scene* scene)
	{
		auto& cameraTransformComponent = scene->m_sceneCamera.getComponent<TransformComponent>();
		if (cameraTransformComponent.rotation.y > 54)
			return true;
		return false;
	}

	void RenderSystem::render_path_1(Scene* scene)
	{
		if (scene)
		{
			m_frameBuffer1->bind();

			CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));
			
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			auto& cameraComponent = scene->m_sceneCamera.getComponent<CameraComponent>();
			auto& cameraTransformComponent = scene->m_sceneCamera.getComponent<TransformComponent>();
			
			for (auto& entity : scene->m_entities)
			{
				if (entity.second.hasComponent<Visual3DComponent>())
				{
					auto& visual3DComponent = entity.second.getComponent<Visual3DComponent>();
					if (visual3DComponent.renderer && visual3DComponent.mesh)
					{
						const auto& vertexArraies = visual3DComponent.mesh->getVertexArraies();
						const auto& indexBuffers = visual3DComponent.mesh->getIndexBuffers();

						for (int i = 0; i < vertexArraies.size(); i++)
						{
							vertexArraies[i]->bind();
							visual3DComponent.renderer->bind();
							TransformComponent tc;
							visual3DComponent.renderer->setMat4("u_mvp", cameraComponent.getProjectionMatrix() * cameraTransformComponent.getInverseWorldMatrix() *
								(entity.second.hasComponent<TransformComponent>() ? entity.second.getComponent<TransformComponent>().getWorldMatrix() : tc.getWorldMatrix()));
							
							if (visual3DComponent.mesh->getTextures()[i])
							{
								visual3DComponent.mesh->getTextures()[i]->bind(0);
							}
							else
							{
								defaultTexture->bind(0);
							}
							
							indexBuffers[i]->bind();
							CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));

							if (visual3DComponent.mesh->getTextures()[i])
							{
								visual3DComponent.mesh->getTextures()[i]->unbind();
							}
							else
							{
								defaultTexture->unbind();
							}

							vertexArraies[i]->unbind();
							visual3DComponent.renderer->unbind();
							indexBuffers[i]->unbind();
						}

					}
				}
			}
			
			m_frameBuffer1->unbind();
		}

	}

	void RenderSystem::render_path_2()
	{

	}

	void RenderSystem::onWindowResize(void* data)
	{
		WindowSize ws = *(WindowSize*)(data);
		m_frameBuffer1->resize(ws.width, ws.height);
	}
}