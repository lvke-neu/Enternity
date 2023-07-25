#include "PostProcessComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	void PostProcessComponent::draw(unsigned int textureId)
	{
		if (renderer && mesh)
		{
			renderer->bind();
			renderer->setUint1("u_postProcessType", 0);
			Texture2D::Bind(textureId, 0);
			mesh->draw();
			Texture2D::UnBind();
			renderer->unbind();
		}
	}

	void PostProcessComponent::release()
	{
		SAFE_DELETE_SET_NULL(renderer);
		SAFE_DELETE_SET_NULL(mesh);
	}
}