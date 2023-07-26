#include "SkyBoxComponent.h"
#include "Engine/Engine.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/ECS/Entity.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/TransformComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Enternity
{
	void SkyBoxComponent::draw()
	{
		if (renderer && mesh && textureCubeMapHDR
			&& renderer->isLoadSucceeded() && mesh->isLoadSucceeded() && textureCubeMapHDR->isLoadSucceeded())
		{
			glDepthFunc(GL_LEQUAL);
			//glEnable(GL_FRAMEBUFFER_SRGB);
			renderer->bind();
			textureCubeMapHDR->bind(0);

			glm::mat4 view = Engine::GetInstance().getSceneManager()->getCurrentScene()->getSceneCamera().getComponent<TransformComponent>().getInverseWorldMatrix();
			glm::mat4 proj = Engine::GetInstance().getSceneManager()->getCurrentScene()->getSceneCamera().getComponent<CameraComponent>().getProjectionMatrix();
			
			renderer->setMat4("u_mvp", proj * glm::mat4(glm::mat3(view)));
			renderer->setInt1("u_entityId", -1);
			mesh->draw();
			
			textureCubeMapHDR->unbind();
			renderer->unbind();

			//glDisable(GL_FRAMEBUFFER_SRGB);
			glDepthFunc(GL_LESS);
		}
	}

	void SkyBoxComponent::release()
	{
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(mesh);
		SAFE_DELETE_SET_NULL(textureCubeMap);
		SAFE_DELETE_SET_NULL(textureCubeMapHDR);
	}
}