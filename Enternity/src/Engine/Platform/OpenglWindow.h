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

		bool windowShouldClose();
		void update();
	private:
		GLFWwindow* m_context{ nullptr };
	};
}