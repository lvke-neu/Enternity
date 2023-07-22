#pragma once

struct GLFWwindow;
namespace Enternity
{
	class UiRender;
	class RenderView
	{
	public:
		RenderView(unsigned int width = 500, unsigned int height = 500, const char* title = "No Title");
		~RenderView();
	public:
		bool windowShouldClose();
		void swapBuffers();
		void setTitle(const char* title);
		void pollEvents();
		UiRender* getUiRender() const;
		void setWindowProperty(unsigned int width, unsigned int height, const char* title, const char* path);
	public:
		void Resize(int width, int height);
		static void Resize(GLFWwindow* window, int width, int height);
		static void KeyTrigger(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseTrigger(GLFWwindow* window, int button, int action, int mods);
		static void MouseMove(GLFWwindow* window, double xpos, double ypos);
		static void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	private:
		GLFWwindow* m_context{ nullptr };
		UiRender* m_uiRender{ nullptr };
	};

	inline UiRender* RenderView::getUiRender() const
	{
		return m_uiRender;
	}
}