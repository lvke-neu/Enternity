#pragma once

namespace Enternity
{
	enum PostprocessType
	{
		None,
		Inversion,
		Grayscale,
		Sharpen,
		Blur,
		EdgeDetection
	};

	class Mesh;
	class Renderer;
	struct PostprocessComponent
	{
		Mesh* mesh{ nullptr };
		Renderer* renderer{ nullptr };
		PostprocessType postprocessType{ None };

		void release();
	};
}