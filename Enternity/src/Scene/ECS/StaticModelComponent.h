#pragma once

namespace Enternity
{
	class Model;
	struct StaticModelComponent
	{
		Model* model{ nullptr };

		void unload();
	};
}
