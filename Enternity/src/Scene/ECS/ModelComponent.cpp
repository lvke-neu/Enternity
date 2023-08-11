#include "ModelComponent.h"
#include "Scene/Model/Model/Model.h"
#include "Scene/Model/Material/Material.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Common/Macro.h"

namespace Enternity
{
	void ModelComponent::unload()
	{
		SAFE_DELETE_SET_NULL(model);
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(material);
	}
}