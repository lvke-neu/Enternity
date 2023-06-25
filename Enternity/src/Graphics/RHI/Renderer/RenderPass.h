#pragma once

namespace Enternity
{
	enum FillMode
	{
		Point = 0,
		Line,
		Fill
	};
	struct RenderPass
	{
		FillMode fillMode{ Fill };
		bool enableDepth{ true };
	};
}