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
		void swapBuffers();

		static void Resize(GLFWwindow* window, int width, int height);
	private:
		GLFWwindow* m_context{ nullptr };
	};

	inline GLFWwindow* OpenglWindow::getContext()
	{
		return m_context;
	}
}

