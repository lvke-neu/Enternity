#pragma once
#include "Graphics/RHI/RHIAsset.h"

namespace Enternity
{
	class Texture2D : public RHIAsset
	{
	public:
		virtual ~Texture2D();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
		void bind();
		void unbind();
	};
}