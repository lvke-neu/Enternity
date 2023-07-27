#pragma once

namespace Enternity
{
	class Model;
	class Renderer;
	struct ModelComponent
	{
		Model* model{ nullptr };
		Renderer* renderer{ nullptr };

		void load(const char* modelPath, const char* rendererPath);
		void unload();
	};
}
