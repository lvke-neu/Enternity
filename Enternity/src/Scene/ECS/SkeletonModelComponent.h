#pragma once

namespace Enternity
{
	class Model;
	struct SkeletonModelComponent
	{
		Model* model{ nullptr };

		void unload();
	};
}
