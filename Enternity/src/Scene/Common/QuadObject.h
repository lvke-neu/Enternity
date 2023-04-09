#pragma once

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class Shader;

	class QuadObject
	{
	public:
		QuadObject(unsigned int texBufferId);
		~QuadObject();
	public:
		void Draw();
	private:
		VertexArray* m_pVertexArray;
		IndexBuffer* m_pIndexBuffer;
		Shader* m_pShader;
		unsigned int m_texBufferId;
	};
}