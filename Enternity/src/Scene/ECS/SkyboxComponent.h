#pragma once
#include <vector>
#include <map>

namespace Enternity
{
	class Mesh;
	class Renderer;
	class CubeMapTexture;
	struct SkyboxComponent
	{
		enum SkyboxType
		{
			None,
			Default,
			Sunset,
			Daylight
		};

		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		CubeMapTexture* cubeMapTexture{ nullptr };
		
		SkyboxType skyboxType{ SkyboxType::Default };

		static std::map<SkyboxType, std::vector<const char*>> FullPaths;

		void release();
	};
}