#include "SkeletonModelComponent.h"
#include "Scene/Model/Model.h"
#include "Common/Macro.h"

namespace Enternity
{
	void SkeletonModelComponent::unload()
	{
		SAFE_DELETE_SET_NULL(model);
	}
}