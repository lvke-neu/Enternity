#pragma once

namespace Enternity
{
	class Model;
	class Material;
	class Renderer;
	struct ModelComponent
	{
		Model* model{ nullptr };
		Renderer* renderer{ nullptr };
		Material* material{ nullptr };
		void unload();
	};
}
