#include "SkyboxComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	std::map<SkyboxComponent::SkyboxType, std::vector<const char*>> SkyboxComponent::FullPaths =
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
		},
		{
			SkyboxType::Daylight,
			{
				{"assets/textures/skybox/daylight/right.png"},
				{"assets/textures/skybox/daylight/left.png"},
				{"assets/textures/skybox/daylight/top.png"},
				{"assets/textures/skybox/daylight/bottom.png"},
				{"assets/textures/skybox/daylight/front.png"},
				{"assets/textures/skybox/daylight/back.png"},
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