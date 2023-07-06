#pragma once

namespace Enternity
{
	class Mesh;
	class Renderer;
	struct PostprocessComponent
	{
		enum  PostprocessType
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
		PostprocessType postprocessType{ PostprocessType::None};

		void release();
	};
}