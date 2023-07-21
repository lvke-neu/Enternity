#pragma once
#include "Graphics/RHI/RHIAsset.h"
//TODO:REMOVE
#include <string>

namespace Enternity
{
	class Renderer : public RHIAsset
	{
	public:
		virtual void load(BlobHolder* blobHolder) override;
		//TODO:REMOVE
	private:
		std::string m_vscode;
		std::string m_gscode;
		std::string m_pscode;
	};
}