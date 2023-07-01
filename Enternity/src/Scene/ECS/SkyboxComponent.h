#pragma once
#include <vector>
#include <map>

namespace Enternity
{
	enum class SkyboxType
	{
		None,
		Default,
		Sunset
	};

	class Mesh;
	class Renderer;
	class CubeMapTexture;
	struct SkyboxComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		CubeMapTexture* cubeMapTexture{ nullptr };
		
		SkyboxType skyboxType{ SkyboxType::Default };

		static std::map<SkyboxType, std::vector<const char*>> FullPaths;

		void release();
	};
}