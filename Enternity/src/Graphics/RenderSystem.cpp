#include "RenderSystem.h"
#include "Scene/Scene.h"
#include "RHI/FrameBuffer/FrameBuffer.h"
#include "Engine/Engine.h"
#include "Engine/Timer.h"
#include "Engine/EventSystem.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/PostProcessComponent.h"
#include "Scene/ECS/SkyBoxComponent.h"
#include "Scene/ECS/Visual3DComponent.h"
#include "Scene/ECS/ModelComponent.h"
#include "Scene/ECS/PBRMaterialComponent.h"
#include "Scene/ECS/SunLightComponent.h"
#include "Scene/Model/Model.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include <glad/glad.h>

namespace Enternity
{
	RenderSystem::RenderSystem()
	{
		m_colorFrameBuffer = new FrameBuffer(100, 100, { ColorAttachmentFormat::RGBA8, ColorAttachmentFormat::RGB8, ColorAttachmentFormat::RED_INTEGER });
		m_postprocessFrameBuffer = new FrameBuffer(100, 100, { ColorAttachmentFormat::RGBA8 });
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
	}

	RenderSystem::~RenderSystem()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
		SAFE_DELETE_SET_NULL(m_colorFrameBuffer);
		SAFE_DELETE_SET_NULL(m_postprocessFrameBuffer);
	}

	void RenderSystem::render(Scene* scene)
	{
		color_path(scene);
		postprocess_path(scene);
	}

	void RenderSystem::color_path(Scene* scene)
	{
		if (scene)
		{
			m_colorFrameBuffer->bind();

			CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));

			color_path_modelPass(scene);
			color_path_skyboxPass(scene);
			
			m_colorFrameBuffer->unbind();
		}
	}

	void RenderSystem::color_path_skyboxPass(Scene* scene)
	{
		auto& skyBoxComponent = scene->m_sceneSkybox.getComponent<SkyBoxComponent>();
		if (skyBoxComponent.renderer && skyBoxComponent.mesh && skyBoxComponent.textureCubeMapHDR && 
			skyBoxComponent.renderer->isLoadSucceeded() && skyBoxComponent.mesh->isLoadSucceeded() && skyBoxComponent.textureCubeMapHDR->isLoadSucceeded())
		{
			glDepthFunc(GL_LEQUAL);
			skyBoxComponent.renderer->bind();
			skyBoxComponent.textureCubeMapHDR->bind(0);

			glm::mat4 view = scene->m_sceneCamera.getComponent<TransformComponent>().getInverseWorldMatrix();
			glm::mat4 proj = scene->m_sceneCamera.getComponent<CameraComponent>().getProjectionMatrix();

			skyBoxComponent.renderer->setMat4("u_mvp", proj * glm::mat4(glm::mat3(view)));
			skyBoxComponent.mesh->draw();

			skyBoxComponent.textureCubeMapHDR->unbind();
			skyBoxComponent.renderer->unbind();

			glDepthFunc(GL_LESS);
		}
	}

	void RenderSystem::color_path_modelPass(Scene* scene)
	{
		for (auto& entity : scene->m_entities)
		{
			if (entity.second.hasComponent<ModelComponent>())
			{
				auto& modelComponent = entity.second.getComponent<ModelComponent>();

				if (modelComponent.renderer && modelComponent.renderer->isLoadSucceeded() &&
					modelComponent.model && modelComponent.model->isLoadSucceeded())
				{
					modelComponent.renderer->bind();

					glm::mat4 model = entity.second.hasComponent<TransformComponent>() ? entity.second.getComponent<TransformComponent>().getWorldMatrix() : glm::mat4(1);
					glm::mat4 view = scene->m_sceneCamera.getComponent<TransformComponent>().getInverseWorldMatrix();
					glm::mat4 proj = scene->m_sceneCamera.getComponent<CameraComponent>().getProjectionMatrix();

					modelComponent.renderer->setMat4("u_m", model);
					modelComponent.renderer->setMat4("u_v", view);
					modelComponent.renderer->setMat4("u_p", proj);

					if (entity.second.hasComponent<PBRMaterialComponent>())
					{
						auto& pbrMaterialComponent = entity.second.getComponent<PBRMaterialComponent>();
						if (pbrMaterialComponent.albedo && pbrMaterialComponent.albedo->isLoadSucceeded())
						{
							pbrMaterialComponent.albedo->bind(0);
						}
						if (pbrMaterialComponent.normal && pbrMaterialComponent.normal->isLoadSucceeded())
						{
							pbrMaterialComponent.normal->bind(1);
						}
						if (pbrMaterialComponent.metallic && pbrMaterialComponent.metallic->isLoadSucceeded())
						{
							pbrMaterialComponent.metallic->bind(2);
						}
						if (pbrMaterialComponent.roughness && pbrMaterialComponent.roughness->isLoadSucceeded())
						{
							pbrMaterialComponent.roughness->bind(3);
						}
						if (pbrMaterialComponent.ao && pbrMaterialComponent.ao->isLoadSucceeded())
						{
							pbrMaterialComponent.ao->bind(4);
						}
					}


					//auto& skyBoxComponent = scene->m_sceneSkybox.getComponent<SkyBoxComponent>();
					//if (skyBoxComponent.textureCubeMapHDR && skyBoxComponent.textureCubeMapHDR->isLoadSucceeded())
					//{
					//	skyBoxComponent.textureCubeMapHDR->bind(5);
					//}

					modelComponent.renderer->setVec3("u_sunLightDirection", -scene->m_sceneSunlight.getComponent<SunLightComponent>().direction);
					modelComponent.renderer->setVec3("u_sunLightColor", scene->m_sceneSunlight.getComponent<SunLightComponent>().color);
					modelComponent.renderer->setVec3("u_cameraPosition", scene->m_sceneCamera.getComponent<TransformComponent>().translation);

					modelComponent.model->draw();

					if (entity.second.hasComponent<PBRMaterialComponent>())
					{
						auto& pbrMaterialComponent = entity.second.getComponent<PBRMaterialComponent>();
						if (pbrMaterialComponent.albedo && pbrMaterialComponent.albedo->isLoadSucceeded())
						{
							pbrMaterialComponent.albedo->unbind(0);
						}
						if (pbrMaterialComponent.normal && pbrMaterialComponent.normal->isLoadSucceeded())
						{
							pbrMaterialComponent.normal->unbind(1);
						}
						if (pbrMaterialComponent.metallic && pbrMaterialComponent.metallic->isLoadSucceeded())
						{
							pbrMaterialComponent.metallic->unbind(2);
						}
						if (pbrMaterialComponent.roughness && pbrMaterialComponent.roughness->isLoadSucceeded())
						{
							pbrMaterialComponent.roughness->unbind(3);
						}
						if (pbrMaterialComponent.ao && pbrMaterialComponent.ao->isLoadSucceeded())
						{
							pbrMaterialComponent.ao->unbind(4);
						}
					}

					modelComponent.renderer->unbind();
				}
			}
		}
	}

	void RenderSystem::postprocess_path(Scene* scene)
	{
		m_postprocessFrameBuffer->bind();

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		auto& postprocessEntity = scene->m_scenePostprocess;
		auto& ppc = postprocessEntity.getComponent<PostProcessComponent>();
		if (ppc.renderer && ppc.mesh)
		{
			ppc.renderer->bind();
			ppc.renderer->setUint1("u_postProcessType", ppc.postprocessType);
			Texture2D::Bind(m_colorFrameBuffer->getTextureId(0), 0);
			ppc.mesh->draw();
			Texture2D::UnBind(0);
			ppc.renderer->unbind();
		}

		m_postprocessFrameBuffer->unbind();
	}

	void RenderSystem::onWindowResize(void* data)
	{
		WindowSize ws = *(WindowSize*)(data);
		m_colorFrameBuffer->resize(ws.width, ws.height);
		m_postprocessFrameBuffer->resize(ws.width, ws.height);
	}
}