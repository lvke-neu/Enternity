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
			[this](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(textureCubeMapHDR);
				textureCubeMapHDR = dynamic_cast<TextureCubeMapHDR*>(asset);
			});
	}

	void SkyBoxComponent::unload()
	{
		SAFE_DELETE_SET_NULL(mesh);
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(textureCubeMapHDR);
	}
}