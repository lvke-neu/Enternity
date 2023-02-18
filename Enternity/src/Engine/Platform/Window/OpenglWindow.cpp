#include "OpenglWindow.h"
#include "Core/Log/Log.h"
#include "Core/Event/WindowResizeEvent.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/Event/TickEvent.h"
#include "Core/Event/EventManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enternity
{
	OpenglWindow::OpenglWindow(const OpenglWindowDescription& desc)
	{
		if (!glfwInit())
		{
			LOG_ERROR("glfw init failed");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		m_context = glfwCreateWindow(desc.Width, desc.Height, desc.Title, nullptr, nullptr);
		if (!m_context)
		{
			LOG_ERROR("glfwWindow create failed");
			return;
		}
		glfwMakeContextCurrent(m_context);
		//don't Limit frame count
		glfwSwapInterval(0);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("glad init failed");
			return;
		}
		
		CHECK_GL_CALL(glEnable(GL_DEPTH_TEST));
		CHECK_GL_CALL((0, 0, desc.Width, desc.Height));

		glfwSetWindowSizeCallback(m_context, Resize);
		glfwSetKeyCallback(m_context, KeyTrigger);
		glfwSetMouseButtonCallback(m_context, MouseTrigger);
		glfwSetCursorPosCallback(m_context, MouseMove);

		LOG_INFO((char*)glGetString(GL_VERSION));
		LOG_INFO((char*)glGetString(GL_VENDOR));
		LOG_INFO((char*)glGetString(GL_RENDERER));
	}

	OpenglWindow::~OpenglWindow()
	{
		glfwTerminate();
	}

	bool OpenglWindow::windowShouldClose()
	{
		return glfwWindowShouldClose(m_context);
	}
	void OpenglWindow::setTitle(const char* title)
	{
		glfwSetWindowTitle(m_context, title);
	}

	void OpenglWindow::swapBuffers(float deltaTime)
	{
		glfwSwapBuffers(m_context);
		glfwPollEvents();
		TickEvent tickEvent(deltaTime);
		EventManager::GetInstance().dispatch(&tickEvent);
	}

	void OpenglWindow::Resize(GLFWwindow* window, int width, int height)
	{
		WindowResizeEvent windowResizeEvent(width, height);
		EventManager::GetInstance().dispatch(&windowResizeEvent);
	}

	void OpenglWindow::KeyTrigger(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			KeyPressedEvent keyPressedEvent((KeyCode)key);
			EventManager::GetInstance().dispatch(&keyPressedEvent);
		}
		else if (action == GLFW_RELEASE)
		{
			KeyReleasedEvent keyReleasedEvent((KeyCode)key);
			EventManager::GetInstance().dispatch(&keyReleasedEvent);
		}
	}

	void OpenglWindow::MouseTrigger(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			MousePressedEvent mousePressedEvent((MouseCode)button, (float)x, (float)y);
			EventManager::GetInstance().dispatch(&mousePressedEvent);
		}

		if (action == GLFW_RELEASE)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			MouseReleasedEvent mouseReleasedEvent((MouseCode)button, (float)x, (float)y);
			EventManager::GetInstance().dispatch(&mouseReleasedEvent);
		}
	}

	void OpenglWindow::MouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			MouseMovedEvent mouseMovedEvent(MouseCode::ButtonLeft, (float)x, (float)y);
			EventManager::GetInstance().dispatch(&mouseMovedEvent);
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			MouseMovedEvent mouseMovedEvent(MouseCode::ButtonRight, (float)x, (float)y);
			EventManager::GetInstance().dispatch(&mouseMovedEvent);
		}
	}
}