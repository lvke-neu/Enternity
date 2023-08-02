#pragma once

namespace Enternity
{
	class Model;
	struct ModelComponent
	{
		Model* model{ nullptr };

		void unload();
	};
}
