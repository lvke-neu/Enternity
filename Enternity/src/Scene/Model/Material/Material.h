#pragma once
#include "Engine/Asset.h"
#include "MaterialDefine.h"
#include <vector>

namespace Enternity
{
	class Material : public Asset
	{
		friend class Model;
	public:
		virtual ~Material();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
	private:
		std::vector<MaterialPropertyImpl> m_materialPropertyImpls;
	};
}