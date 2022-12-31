#include "OpenglWindow.h"
#include <GLFW/glfw3.h>

BEGIN_ENTERNITY

OpenglWindow::OpenglWindow():
	m_width(800),
	m_height(600),
	m_title("OpenglWindow")
{
	Initialize();
}

OpenglWindow::OpenglWindow(unsigned int width, unsigned int height, const char* title):
	m_width(width),
	m_height(height),
	m_title(title)
{
	Initialize();
}

OpenglWindow::~OpenglWindow()
{
	glfwTerminate();
}

void OpenglWindow::Initialize()
{
	
	//initialize glfw

	GLFWwindow* window;

}

void OpenglWindow::Run()
{

}

END_ENTERNITY
