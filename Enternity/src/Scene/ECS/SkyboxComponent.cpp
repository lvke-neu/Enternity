#include "SkyboxComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	std::map<SkyboxType, std::vector<const char*>> SkyboxComponent::FullPaths =
	{
		{
			SkyboxType::None, 
			{
				
			}
		},
		{
			SkyboxType::Default,
			{
				{"assets/textures/skybox/default/right.jpg"},
				{"assets/textures/skybox/default/left.jpg"},
				{"assets/textures/skybox/default/top.jpg"},
				{"assets/textures/skybox/default/bottom.jpg"},
				{"assets/textures/skybox/default/front.jpg"},
				{"assets/textures/skybox/default/back.jpg"}
			}

		},
		{
			SkyboxType::Sunset,
			{
				{"assets/textures/skybox/sunset/right.bmp"},
				{"assets/textures/skybox/sunset/left.bmp"},
				{"assets/textures/skybox/sunset/top.bmp"},
				{"assets/textures/skybox/sunset/bottom.bmp"},
				{"assets/textures/skybox/sunset/front.bmp"},
				{"assets/textures/skybox/sunset/back.bmp"},
			}
		}
	};

	void SkyboxComponent::release()
	{
		SAFE_DELETE_SET_NULL(mesh);
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(cubeMapTexture);
	}
}