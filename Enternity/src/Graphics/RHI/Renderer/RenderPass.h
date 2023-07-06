#pragma once

namespace Enternity
{
	struct RenderPass
	{
		enum FillMode
		{
			Point = 0,
			Line,
			Fill
		};

		FillMode fillMode{ Fill };
		bool enableDepth{ true };
	};
}