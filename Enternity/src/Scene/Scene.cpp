#include "Scene.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "Common/Macro.h"
#include "CameraController.h"
//TODO:
#include "ECS/Visual3DComponent.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/Mesh/MeshProvider.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Mesh/VertexArray.h"
#include "Graphics/RHI/Mesh/IndexBuffer.h"
#include "Graphics/RHI/Renderer/RendererProvider.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Texture/TextureProvider.h"


#include <glad/glad.h>

namespace Enternity
{
	Scene::Scene()
	{
		m_sceneCamera = createEntity();
		
		auto& comp = m_sceneCamera.addComponent<TransformComponent>();
		comp.translation = glm::vec3(0, 0, 20);
		m_sceneCamera.addComponent<CameraComponent>();

		m_cameraController = new CameraController(&m_sceneCamera);

		//TODO:
		m_testVisual3DComponent = createEntity();
		m_testVisual3DComponent.addComponent<TransformComponent>();
		auto& v3d  = m_testVisual3DComponent.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test.vert", "assets/shaders/test/test.frag",
			[&](Renderer* render)
			{
				auto& comp = m_testVisual3DComponent.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/nanosuit/nanosuit.obj", 
			[&](Mesh* mesh) 
			{
				auto& comp = m_testVisual3DComponent.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});
		
		m_testVisual3DComponent2 = createEntity();
		m_testVisual3DComponent2.addComponent<TransformComponent>();
		auto& v3d2 = m_testVisual3DComponent2.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[&](Renderer* render)
			{
				auto& comp = m_testVisual3DComponent2.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/models/Cube.fbx",
			[&](Mesh* mesh)
			{
				auto& comp = m_testVisual3DComponent2.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});
		Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTextureAsyn("assets/textures/skybox.jpeg",
			[&](Texture* texture)
			{
				auto& comp = m_testVisual3DComponent2.getComponent<Visual3DComponent>();
				comp.texture = texture;
			});
	}

	Scene::~Scene()
	{
		for (auto& entity : m_entities)
		{
			m_registry.destroy(entity.second.getEnttID());
		}
		m_entities.clear();

		SAFE_DELETE_SET_NULL(m_cameraController);
	}

	Entity Scene::createEntity()
	{
		Entity entity(&m_registry);
		m_entities.insert({ entity.getEnttID(), entity });

		return entity;
	}

	Entity Scene::getEntity(entt::entity id)
	{
		auto it = m_entities.find(id);
		if (it != m_entities.end())
		{
			return m_entities[id];
		}

		return Entity();
	}

	void Scene::deleteEntity(entt::entity id)
	{
		auto it = m_entities.find(id);
		if (it != m_entities.end())
		{
			m_entities.erase(id);
		}
	}

	void Scene::tick(float deltaTime)
	{
		CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		auto& cameraComponent = m_sceneCamera.getComponent<CameraComponent>();
		auto& cameraTransformComponent = m_sceneCamera.getComponent<TransformComponent>();
		auto& visual3DComponent = m_testVisual3DComponent.getComponent<Visual3DComponent>();
		auto& v3dTransformComponent = m_testVisual3DComponent.getComponent<TransformComponent>();

		if (visual3DComponent.renderer && visual3DComponent.mesh)
		{
			
			
			const auto& vertexArraies = visual3DComponent.mesh->getVertexArraies();
			const auto& indexBuffers = visual3DComponent.mesh->getIndexBuffers();

			for (int i =0; i<vertexArraies.size();i++)
			{
				vertexArraies[i]->bind();
				visual3DComponent.renderer->bind();
				visual3DComponent.renderer->setMat4("u_mvp", cameraComponent.getProjectionMatrix() * cameraTransformComponent.getInverseWorldMatrix() * v3dTransformComponent.getWorldMatrix());
				indexBuffers[i]->bind();
				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));
			}

			
			for (int i = 0; i < vertexArraies.size(); i++)
			{
				vertexArraies[i]->unbind();
				visual3DComponent.renderer->unbind();
				indexBuffers[i]->unbind();
			}
		}


		auto& visual3DComponent2 = m_testVisual3DComponent2.getComponent<Visual3DComponent>();
		auto& v3dTransformComponent2 = m_testVisual3DComponent2.getComponent<TransformComponent>();

		if (visual3DComponent2.renderer && visual3DComponent2.mesh && visual3DComponent2.texture)
		{


			const auto& vertexArraies = visual3DComponent2.mesh->getVertexArraies();
			const auto& indexBuffers = visual3DComponent2.mesh->getIndexBuffers();

			for (int i = 0; i < vertexArraies.size(); i++)
			{
				vertexArraies[i]->bind();
				visual3DComponent2.renderer->bind();
				visual3DComponent2.renderer->setMat4("u_mvp", cameraComponent.getProjectionMatrix() * cameraTransformComponent.getInverseWorldMatrix() * v3dTransformComponent2.getWorldMatrix());
				visual3DComponent2.texture->bind(0);
				indexBuffers[i]->bind();
				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));
			}


			for (int i = 0; i < vertexArraies.size(); i++)
			{
				vertexArraies[i]->unbind();
				visual3DComponent2.renderer->unbind();
				indexBuffers[i]->unbind();
			}
		}
	}
}