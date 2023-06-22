#pragma once

namespace Enternity
{
	class MeshAsset;
	class VertexArray
	{
	public:
		VertexArray(MeshAsset* meshAsset, unsigned int location);
		~VertexArray();
	public:
		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
		unsigned int m_vbId;
	};
}