#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	class Texture;
	struct ParticleComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		Texture* texture{ nullptr };

		void release();
	};
}