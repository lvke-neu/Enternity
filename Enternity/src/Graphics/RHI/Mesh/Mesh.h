#pragma once
#include "Engine/Asset.h"

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class Mesh : public Asset
	{
	public:
		virtual ~Mesh();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
		
		void draw();
	private:
		void bind();
		void unbind();
	private:
		VertexArray* m_vertexArray{ nullptr };
	};
}