#include "PostProcessComponent.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/FrameBuffer/FrameBuffer.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	void PostProcessComponent::draw()
	{
		if (renderer && mesh)
		{
			renderer->bind();
			renderer->setUint1("u_postProcessType", postprocessType);
			Texture2D::Bind(Engine::GetInstance().getGraphicsSystem()->getColorFrameBuffer()->getTextureId(0), 0);
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