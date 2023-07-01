#include "Visual3DComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Common/Macro.h"

namespace Enternity
{
	void Visual3DComponent::release()
	{
		SAFE_DELETE_SET_NULL(mesh);
		SAFE_DELETE_SET_NULL(renderer);
	}
}