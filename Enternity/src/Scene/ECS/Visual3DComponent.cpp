#include "Visual3DComponent.h"
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
	void Visual3DComponent::draw()
	{
		if (renderer && mesh && texture2D
			&& renderer->isLoadSucceeded() && mesh->isLoadSucceeded() && texture2D->isLoadSucceeded())
		{
			renderer->bind();
			texture2D->bind(0);

			glm::mat4 view = Engine::GetInstance().getSceneManager()->getCurrentScene()->getSceneCamera().getComponent<TransformComponent>().getInverseWorldMatrix();
			glm::mat4 proj = Engine::GetInstance().getSceneManager()->getCurrentScene()->getSceneCamera().getComponent<CameraComponent>().getProjectionMatrix();

			renderer->setMat4("u_mvp", proj * view);
			mesh->draw();

			texture2D->unbind();
			renderer->unbind();
		}
	}

	void Visual3DComponent::release()
	{
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(mesh);
		SAFE_DELETE_SET_NULL(texture2D);
	}
}