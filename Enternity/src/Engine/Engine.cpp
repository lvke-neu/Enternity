#include "Engine.h"
#include "Log/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TestDrawable/Triangle.h"

BEGIN_ENTERNITY

#define WINDOW_WIDHT 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Enternity Engine"

void OnResize(GLFWwindow* context, int width, int height)
{
	glViewport(0, 0, width, height);
	LOG_INFO("Resize:" + std::to_string(width) + "," + std::to_string(height));
}

void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		LOG_INFO(std::to_string(key) + " release");
	}

	if (action == GLFW_PRESS)
	{
		LOG_INFO(std::to_string(key) + " press");
	}
}

void MouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		LOG_INFO(std::to_string(button) + " release");
	}

	if (action == GLFW_PRESS)
	{
		LOG_INFO(std::to_string(button) + " press");
	}
}

void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
{
	//LOG_INFO("mouse pos:" + std::to_string(xpos) + "," + std::to_string(ypos));
}


Engine::~Engine()
{
	glfwTerminate();
}

bool Engine::Initialize()
{
	//glfwInit
	if (!glfwInit())
	{
		LOG_ERROR("glfw init failed");
		return false;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//contex
	m_context = glfwCreateWindow(WINDOW_WIDHT, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
	if (!m_context)
	{
		LOG_ERROR("glfwWindow create failed");
		return false;
	}
	glfwMakeContextCurrent(m_context);

	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("glad init failed");
		return false;
	}

	//hardware info
	LOG_INFO((char*)glGetString(GL_VERSION));
	LOG_INFO((char*)glGetString(GL_VENDOR));
	LOG_INFO((char*)glGetString(GL_RENDERER));


	//all kind of callback
	glViewport(0, 0, WINDOW_WIDHT, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(m_context, OnResize);
	glfwSetKeyCallback(m_context, KeyEvent);
	glfwSetMouseButtonCallback(m_context, MouseButtonEvent);
	glfwSetCursorPosCallback(m_context, MouseMoveEvent);

	m_timer.Reset();
	m_timer.Start();


	LOG_INFO("Engine initialization is complete");

	return true;
}

void Engine::Run()
{
	
	Triangle triangle;
	while (!glfwWindowShouldClose(m_context))
	{
		m_timer.Tick();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw
		triangle.draw();

		glfwSwapBuffers(m_context);
		glfwPollEvents();
	}
}


END_ENTERNITY