#include "RendererProvider.h"
#include "Renderer.h"
#include "RendererAsset.h"
#include "Common/Macro.h"

namespace Enternity
{
	Renderer* RendererProvider::getRenderer(const char* vsFullPath, const char* psFullPath)
	{
		RendererAsset* vsRendererAsset = new RendererAsset(vsFullPath);
		vsRendererAsset->load(0);

		RendererAsset* psRendererAsset = new RendererAsset(psFullPath);
		psRendererAsset->load(0);

		Renderer* renderer = new Renderer(vsRendererAsset, psRendererAsset);

		SAFE_DELETE_SET_NULL(vsRendererAsset);
		SAFE_DELETE_SET_NULL(psRendererAsset);

		return renderer;
	}
}