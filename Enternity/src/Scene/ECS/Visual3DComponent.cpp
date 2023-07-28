#include "Visual3DComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	void Visual3DComponent::unload()
	{
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(mesh);
		SAFE_DELETE_SET_NULL(texture2D);
	}
}