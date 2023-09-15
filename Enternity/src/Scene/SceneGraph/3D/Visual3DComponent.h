#pragma once
#include "../Component.h"

namespace Enternity
{
	class Visual3DComponent : public Component
	{
		RTTR_ENABLE(Component);
	public:
		Visual3DComponent();
		~Visual3DComponent();
	public:
		GET_CLASS_NAME(Visual3DComponent);
	};


}