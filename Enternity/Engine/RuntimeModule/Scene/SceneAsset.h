#pragma once
#include "RuntimeModule/Asset/Asset.h"
#include <string>

namespace Enternity
{
	class SceneAsset : public Asset
	{
	public:
		virtual ~SceneAsset();
		virtual void doLoad() override;
		virtual void callBack() override;
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