#include "SkyBoxComponent.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
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

	void SkyBoxComponent::load(const char* __texturePath)
	{
		std::string tmpTexturePath(__texturePath);

		Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=cube",
			[this](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(mesh);
				mesh = dynamic_cast<Mesh*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/skybox/skybox.rdr",
			[this](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(renderer);
				renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset(__texturePath,
			[tmpTexturePath, this](Asset* asset)
			{
				auto pos = tmpTexturePath.find("texture://CUBE_MAP_HDR?");
				if (pos != std::string::npos)
				{
					texturePath = tmpTexturePath.substr(pos + 23);
				}

				SAFE_DELETE_SET_NULL(textureCubeMapHDR);
				textureCubeMapHDR = dynamic_cast<TextureCubeMapHDR*>(asset);
			});
	}

	void SkyBoxComponent::draw()
	{
		if (renderer && mesh && textureCubeMapHDR
			&& renderer->isLoadSucceeded() && mesh->isLoadSucceeded() && textureCubeMapHDR->isLoadSucceeded())
		{
			glDepthFunc(GL_LEQUAL);
			renderer->bind();
			textureCubeMapHDR->bind(0);

			glm::mat4 view = Engine::GetInstance().getSceneManager()->getCurrentScene()->getSceneCamera().getComponent<TransformComponent>().getInverseWorldMatrix();
			glm::mat4 proj = Engine::GetInstance().getSceneManager()->getCurrentScene()->getSceneCamera().getComponent<CameraComponent>().getProjectionMatrix();
			
			renderer->setMat4("u_mvp", proj * glm::mat4(glm::mat3(view)));
			mesh->draw();
			
			textureCubeMapHDR->unbind();
			renderer->unbind();

			glDepthFunc(GL_LESS);
		}
	}

	void SkyBoxComponent::unload()
	{
		SAFE_DELETE_SET_NULL(mesh);
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(textureCubeMapHDR);
	}
}