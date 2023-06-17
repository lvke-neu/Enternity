#pragma once
#include "../Asset.h"
#include <string>

namespace Enternity
{
	class Blob;
	class WindowsFileAsset : public Asset
	{
	public:
		WindowsFileAsset(const std::string& fullPath);
		~WindowsFileAsset();
	public:
		Blob* getBlob() const;
	private:
		virtual void doLoad() override;
	private:
		std::string m_fullPath{ "" };
		Blob* m_content{ nullptr };
	};

	inline Blob* WindowsFileAsset::getBlob() const 
	{
		return m_content;
	}
}