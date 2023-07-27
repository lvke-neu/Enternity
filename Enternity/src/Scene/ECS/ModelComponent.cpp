#include "ModelComponent.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Scene/Model/Model.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Common/Macro.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Enternity
{
	void ModelComponent::load(const char* modelPath, const char* rendererPath)
	{
		Engine::GetInstance().getAssetLoader()->getAsset(modelPath,
			[&](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(model);
				model = dynamic_cast<Model*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset(rendererPath,
			[&](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(renderer);
				renderer = dynamic_cast<Renderer*>(asset);
			});
	}

	void ModelComponent::unload()
	{
		SAFE_DELETE_SET_NULL(model);
		SAFE_DELETE_SET_NULL(renderer);
	}
}