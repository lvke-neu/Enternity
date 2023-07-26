#include "PostProcessComponent.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/FrameBuffer/FrameBuffer.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	void PostProcessComponent::draw()
	{
		if (renderer && mesh)
		{
			renderer->bind();
			renderer->setUint1("u_postProcessType", postprocessType);
			Texture2D::Bind(Engine::GetInstance().getGraphicsSystem()->getColorFrameBuffer()->getTextureId(0), 0);
			mesh->draw();
			Texture2D::UnBind();
			renderer->unbind();
		}
	}

	void PostProcessComponent::load()
	{
		Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=plane",
			[this](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(mesh);
				mesh = dynamic_cast<Mesh*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/postprocess/postprocess.rdr",
			[this](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(renderer);
				renderer = dynamic_cast<Renderer*>(asset);
			});
	}

	void PostProcessComponent::unload()
	{
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(mesh);
	}
}