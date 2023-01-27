#include "ShadowMapManager.h"
#include "Engine/Engine.h"

BEGIN_ENTERNITY

const unsigned int SHADOW_WIDTH = 1024;
const unsigned int SHADOW_HEIGHT = 1024;

ShadowMapManager::ShadowMapManager()
{
	m_FrameBufferShadowMap = new FrameBufferShadowMap(SHADOW_WIDTH, SHADOW_HEIGHT);
}

ShadowMapManager::~ShadowMapManager()
{
	SAFE_DELETE_SET_NULL(m_FrameBufferShadowMap);
}

void ShadowMapManager::Begin()
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	m_FrameBufferShadowMap->Bind();
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMapManager::End()
{
	glViewport(0, 0, Engine::GetInstance().GetFrameBufferEx()->GetFBSpec().m_Width, Engine::GetInstance().GetFrameBufferEx()->GetFBSpec().m_Height);
	m_FrameBufferShadowMap->UnBind();
}


END_ENTERNITY
