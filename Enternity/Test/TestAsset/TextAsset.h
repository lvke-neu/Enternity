#pragma once
#include "RuntimeModule/Asset/Asset.h"
#include "Utility/Utility.h"
#include <string>

namespace Enternity
{
	class Blob;
	class TextAsset : public Asset
	{
	public:
		virtual ~TextAsset();
		virtual void doLoad() override;
	public:
		void setPath(const std::string& path) 
		{
			m_path = path;
		}
		inline Blob* getBlob()
		{
			return m_data;
		}
	private:
		Blob* m_data;
		std::string m_path;
	};
}