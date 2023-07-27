#pragma once
#include <string>

namespace Enternity
{
	class Mesh;
	class Renderer;
	class TextureCubeMapHDR;
	struct SkyBoxComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		TextureCubeMapHDR* textureCubeMapHDR{ nullptr };

		void load(const char* _texturePath);
		void unload();
	};
}
