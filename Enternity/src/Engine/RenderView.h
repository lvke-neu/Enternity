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
	public:
		static void Resize(GLFWwindow* window, int width, int height);
		static void KeyTrigger(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseTrigger(GLFWwindow* window, int button, int action, int mods);
		static void MouseMove(GLFWwindow* window, double xpos, double ypos);
	private:
		GLFWwindow* m_context{ nullptr };
		UiRender* m_uiRender{ nullptr };
	};
}