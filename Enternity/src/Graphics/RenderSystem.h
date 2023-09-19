#pragma once
#include <set>

namespace Enternity
{
	class Command;
	class FrameBuffer;
	class RenderSystem
	{
	protected:
		RenderSystem();
		virtual ~RenderSystem();
	public:
		void addCommand(Command* command);
		void tick();
		FrameBuffer* getColorFrameBuffer();
	private:
		void onWindowResize(void* data);
	private:
		FrameBuffer* m_colorFrameBuffer{ nullptr };
		std::set<Command*> m_commands;
	};

	inline FrameBuffer* RenderSystem::getColorFrameBuffer()
	{
		return m_colorFrameBuffer;
	}
}