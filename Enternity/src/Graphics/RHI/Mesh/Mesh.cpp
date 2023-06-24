#include "Mesh.h"
#include "MeshAsset.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../Texture/Texture.h"
#include "Common/Macro.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Texture/TextureProvider.h"

namespace Enternity
{
	Mesh::Mesh(MeshAsset* meshAsset)
	{
		if (meshAsset)
		{
			m_vertexArraies.resize(meshAsset->getVertices().size());
			m_indexBuffers.resize(meshAsset->getIndices().size());
			m_textures.resize(meshAsset->getMaterials().size());

			for (int i = 0; i < m_vertexArraies.size(); ++i)
			{
				m_vertexArraies[i] = new VertexArray{ meshAsset, (unsigned int)i };
			}

			for (int i = 0; i < m_indexBuffers.size(); ++i)
			{
				m_indexBuffers[i] = new IndexBuffer{ meshAsset, (unsigned int)i };
			}
			
			for (int i = 0; i < m_textures.size(); ++i)
			{
				Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTextureAsyn(meshAsset->getMaterials()[i].c_str(),
					[=](Texture* texture)
					{
						m_textures[i] = texture;
					});
			}
		}
	}

	Mesh::~Mesh()
	{
		for (auto& vertexArray : m_vertexArraies)
		{
			SAFE_DELETE_SET_NULL(vertexArray);
		}
		
		for (auto& indexBuffer : m_indexBuffers)
		{
			SAFE_DELETE_SET_NULL(indexBuffer);
		}

		for (auto& texture : m_textures)
		{
			SAFE_DELETE_SET_NULL(texture);
		}
	}

	const std::vector<VertexArray*>& Mesh::getVertexArraies() const
	{
		return m_vertexArraies;
	}

	const std::vector <IndexBuffer*>& Mesh::getIndexBuffers() const
	{
		return m_indexBuffers;
	}	
	
	const std::vector <Texture*>& Mesh::getTextures() const
	{
		return m_textures;
	}
}