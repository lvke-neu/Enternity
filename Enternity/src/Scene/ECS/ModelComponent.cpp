#include "ModelComponent.h"
#include "Scene/Model/Model.h"
#include "Common/Macro.h"

namespace Enternity
{
	void ModelComponent::unload()
	{
		SAFE_DELETE_SET_NULL(model);
	}
}