/***************************************************************************************
Author: lvke
Date:2023/1/27 18:41
Description:
ShadowMap Manager
****************************************************************************************/

#pragma once

#include "Macro/Macro.h"
#include "Renderer/FrameBuffer.h"

BEGIN_ENTERNITY

class ShadowMapManager
{
	SINGLETON(ShadowMapManager);
public:
	void Begin();
	void End();

	void BindShadowMap(unsigned int slot)
	{
		CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_FrameBufferShadowMap->GetTextureRendererId()));
	}

	inline FrameBufferShadowMap* GetFrameBufferShadowMap() const
	{
		return m_FrameBufferShadowMap;
	}
private:
	ShadowMapManager();
	~ShadowMapManager();
	ShadowMapManager(const ShadowMapManager&) = default;
	ShadowMapManager& operator=(const ShadowMapManager&) = default;
private:
	FrameBufferShadowMap* m_FrameBufferShadowMap{ nullptr };
};

END_ENTERNITY