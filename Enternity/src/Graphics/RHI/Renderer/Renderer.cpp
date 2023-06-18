#include "Renderer.h"
#include "RendererAsset.h"
#include "Engine/Blob.h"

namespace Enternity
{
	Renderer::Renderer(RendererAsset* vsRendererAsset, RendererAsset* psRendererAsset, RendererAsset* gsRendererAsset)
	{
		//TODO:remove
		if (vsRendererAsset && vsRendererAsset->getBlob())
		{
			m_vs = std::string((char*)vsRendererAsset->getBlob()->getData(), vsRendererAsset->getBlob()->getLength());
			m_ps = std::string((char*)psRendererAsset->getBlob()->getData(), psRendererAsset->getBlob()->getLength());
		}
	}

	Renderer::~Renderer()
	{

	}
}