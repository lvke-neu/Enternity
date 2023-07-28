#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	class Texture2D;
	struct Visual3DComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		Texture2D* texture2D{ nullptr };

		void unload();
	};
}
