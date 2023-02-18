/***************************************************************************************
Author: lvke
Date:2023/2/18 16:19
Description:
ShaderAssetImpl
****************************************************************************************/
#pragma once
#include "Core/Asset/Asset.h"

namespace Enternity
{
	class IEvent;
	class Shader;
	class ShaderAssetImpl
	{
	public:
		ShaderAssetImpl();
		~ShaderAssetImpl();
		void load(const std::string& vsFilePath, const std::string& psFilePath);
		void unLoad();
		inline Shader* getShader();
	protected:
		void loadImpl(IEvent* event);
	private:
		Asset m_vsAsset;
		Asset m_psAsset;

		Shader* m_shader{ nullptr };
	};

	inline Shader* ShaderAssetImpl::getShader()
	{
		return m_shader;
	}
}