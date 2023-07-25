#include "PostProcessComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Common/Macro.h"

namespace Enternity
{
	void PostProcessComponent::draw()
	{
		if (renderer && mesh && texture2D)
		{
			renderer->bind();
			renderer->setUint1("u_postProcessType", 1);
			texture2D->bind(0);
			mesh->draw();

			texture2D->unbind();
			renderer->unbind();
		}
	}

	void PostProcessComponent::release()
	{
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(mesh);
		SAFE_DELETE_SET_NULL(texture2D);
	}
}