#pragma once

namespace Enternity
{
	class Model;
	class Renderer;
	struct ModelComponent
	{
		Model* model{ nullptr };
		Renderer* renderer{ nullptr };

		void unload();
	};
}
