#include "StaticModelComponent.h"
#include "Scene/Model/Model/Model.h"
#include "Common/Macro.h"

namespace Enternity
{
	void StaticModelComponent::unload()
	{
		SAFE_DELETE_SET_NULL(model);
	}
}