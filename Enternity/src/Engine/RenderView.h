#pragma once

struct GLFWwindow;
namespace Enternity
{
	class UiRender;
	class RenderView
	{
	public:
		RenderView(unsigned int width, unsigned int height, const char* title);
		~RenderView();
	public:
		bool windowShouldClose();
		void swapBuffers();
		void setTitle(const char* title);
	private:
		GLFWwindow* m_context{ nullptr };
		UiRender* m_uiRender{ nullptr };
	};
}