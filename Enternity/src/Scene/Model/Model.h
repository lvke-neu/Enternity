#pragma once
#include "Engine/Asset.h"
#include <string>
#include <vector>

namespace Enternity
{
	class Mesh;
	class Model : public Asset
	{
	public:
		virtual ~Model();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
		void draw();
		const std::string& getPath();
	private:
		std::vector<Mesh*> m_meshs;
		std::string m_path;
	};

	inline const std::string& Model::getPath()
	{
		return m_path;
	}
}