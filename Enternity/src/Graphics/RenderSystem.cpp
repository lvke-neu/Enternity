#include "RenderSystem.h"
#include "Engine/Engine.h"
#include "Engine/Command.h"
#include "Engine/EventSystem.h"
#include "RHI/FrameBuffer/FrameBuffer.h"
#include <glad/glad.h>

namespace Enternity
{
	const unsigned int SHADOW_MAP_WIDTH = 4096;
	const unsigned int SHADOW_MAP_HEIGHT = 4096;
	const float ORTHO_LENGTH = 50.0f;

	RenderSystem::RenderSystem()
	{
		m_colorFrameBuffer = new FrameBuffer(100, 100, { ColorAttachmentFormat::RGBA8, ColorAttachmentFormat::RGB8, ColorAttachmentFormat::RED_INTEGER });
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
	}

	RenderSystem::~RenderSystem()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
		SAFE_DELETE_SET_NULL(m_colorFrameBuffer);
	}

	void RenderSystem::addCommand(Command* command)
	{
		if (!command)
		{
			return;
		}
		m_commands.emplace(command);
	}

	void RenderSystem::tick()
	{
		m_colorFrameBuffer->bind();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		for (const auto& command : m_commands)
		{
			command->execute();
		}
		m_colorFrameBuffer->unbind();
		m_commands.clear();
	}

	void RenderSystem::onWindowResize(void* data)
	{
		WindowSize ws = *(WindowSize*)(data);
		m_colorFrameBuffer->resize(ws.width, ws.height);
	}
}