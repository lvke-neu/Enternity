/***************************************************************************************
Author: lvke
Date:2023/2/5 22:50
Description:
Opengl Window Wrapper
****************************************************************************************/
#pragma once

struct GLFWwindow;
namespace Enternity
{
	class OpenglWindow
	{
	public:
		struct OpenglWindowDescription
		{
			unsigned int Width;
			unsigned int Height;
			const char* Title;
		};
	public:
		OpenglWindow(const OpenglWindowDescription& desc);
		~OpenglWindow();

		inline GLFWwindow* getContext();

		bool windowShouldClose();
		void setTitle(const char* title);
		void swapBuffers(float deltaTime);

		static void Resize(GLFWwindow* window, int width, int height);
		static void KeyTrigger(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseTrigger(GLFWwindow* window, int button, int action, int mods);
		static void MouseMove(GLFWwindow* window, double xpos, double ypos);
	private:
		GLFWwindow* m_context{ nullptr };
	};

	inline GLFWwindow* OpenglWindow::getContext()
	{
		return m_context;
	}
}

