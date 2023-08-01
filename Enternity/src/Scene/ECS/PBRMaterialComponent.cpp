#include "PBRMaterialComponent.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	void PBRMaterialComponent::unload()
	{
		SAFE_DELETE_SET_NULL(albedo);
		SAFE_DELETE_SET_NULL(normal);
		SAFE_DELETE_SET_NULL(metallic);
		SAFE_DELETE_SET_NULL(roughness);
		SAFE_DELETE_SET_NULL(ao);
	}
}