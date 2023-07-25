#pragma once
#include "Graphics/RHI/RHIAsset.h"

namespace Enternity
{
	//#########################################################################################
	class Texture2D : public RHIAsset
	{
	public:
		virtual ~Texture2D();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
		void bind(unsigned int slot);
		void unbind();
	public:
		//bind existing texture
		static void Bind(unsigned int renderId, unsigned int slot);
		static void UnBind();
	};

	//#########################################################################################
	class Texture2DHDR : public Texture2D
	{
	public:
		virtual void load(BlobHolder* blobHolder) override;
	};

	//#########################################################################################
	class TextureCubeMap : public RHIAsset
	{
	public:
			virtual ~TextureCubeMap();
		public:
			virtual void load(BlobHolder* blobHolder) override;
			virtual void unload() override;
			void bind(unsigned int slot);
			void unbind();
	};
}