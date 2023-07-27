#pragma once
#include "Engine/Asset.h"
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
	private:
		std::vector<Mesh*> m_meshs;
	};
}