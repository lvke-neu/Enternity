#pragma once
#include "Engine/Asset.h"
#include <vector>

namespace Enternity
{
	class Mesh;
	class Material;
	class Model : public Asset
	{
		friend class Model3DComponent;
	public:
		virtual ~Model();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
	private:
		std::vector<Mesh*> m_meshs;
		std::vector<Material*> m_materials;
		std::vector<std::string> m_meshNames;
	};
}