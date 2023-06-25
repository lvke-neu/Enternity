#pragma once
#include "Engine/Asset.h"
#include <string>

namespace Enternity
{
	class Texture;
	class Blob;
	class RendererAsset : public Asset
	{
		friend class Texture;
	public:
		RendererAsset(const std::string& fullPath);
		~RendererAsset();
	public:
		Blob* getBlob() const;
		const std::string& getFullPath() const;
	private:
		virtual void doLoad() override;
	private:
		std::string m_fullPath{ "" };
		Blob* m_content{ nullptr };
	};

	inline Blob* RendererAsset::getBlob() const
	{
		return m_content;
	}

	inline const std::string& RendererAsset::getFullPath() const
	{
		return m_fullPath;
	}
}

