#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	class CubeMapTexture;
	struct SkyboxComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		CubeMapTexture* cubeMapTexture{ nullptr };
		bool enable{ true };
		void release();
	};
}