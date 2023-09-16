#pragma once
#include "Engine/Asset.h"
#include "MaterialDefine.h"
#include "Common/Macro.h"
#include <vector>

namespace Enternity
{
	class Mesh;
	class Renderer;
	class Material;
	class Model : public Asset
	{
	public:
		virtual ~Model();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;

		void draw(Renderer* renderer);
		void setUseTexture(bool b);
		bool getUseTexture();
		std::vector<MaterialPropertyImpl>& getMaterials();
		GET(std::vector<Mesh*>, meshs);
	private:
		std::vector<Mesh*> m_meshs;
		std::vector<MaterialPropertyImpl> m_materials;
		bool m_bUseTexture{ true };
	};

	inline void Model::setUseTexture(bool b)
	{
		m_bUseTexture = b;
	}

	inline bool Model::getUseTexture()
	{
		return m_bUseTexture;
	}

	inline std::vector<MaterialPropertyImpl>& Model::getMaterials()
	{
		return m_materials;
	}
}