/***************************************************************************************
Author: lvke
Date:2023/2/18 16:19
Description:
RenderPassAssetImpl
****************************************************************************************/
#pragma once
#include "Core/Asset/Asset.h"
#include <unordered_map>

namespace Enternity
{
	enum class RenderState
	{
		WireFrame,
		Depth,
		Stencil,
		Cull
	};

	class IEvent;
	class Shader;
	class RenderPassAssetImpl
	{
	public:
		RenderPassAssetImpl();
		~RenderPassAssetImpl();

		void load(const std::string& vsFilePath, const std::string& psFilePath);
		void unLoad();

		void setRenderState(RenderState state, bool enable);
		bool getRenderState(RenderState state);

		inline Shader* getShader();
	protected:
		void loadImpl(IEvent* event);
	private:
		Asset m_vsAsset;
		Asset m_psAsset;

		Shader* m_shader{ nullptr };
		std::unordered_map<RenderState, bool> m_renderStates;
	};

	inline Shader* RenderPassAssetImpl::getShader()
	{
		return m_shader;
	}
}