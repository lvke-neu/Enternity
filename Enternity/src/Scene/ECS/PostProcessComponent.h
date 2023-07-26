#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	struct PostProcessComponent
	{
		enum PostProcessType
		{
			None,
			Inversion,
			Grayscale,
			Sharpen,
			Blur,
			EdgeDetection
		};
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		PostProcessType postprocessType{ None };

		void load();
		void unload();
		void draw();
	};
}
