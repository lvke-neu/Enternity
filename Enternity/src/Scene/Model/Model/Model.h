#pragma once
#include "Engine/Asset.h"
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

		void draw(Renderer* renderer, Material* material);
	private:
		std::vector<Mesh*> m_meshs;
	};
}