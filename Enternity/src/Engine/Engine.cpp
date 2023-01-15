#include "Engine.h"
#include "Log/Log.h"
#include "Imgui/ImguiManager.h"
#include "Event/InputEventManager.h"
#include "Event/TickEventManager.h"
#include "Scene/SceneManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

BEGIN_ENTERNITY

#define WINDOW_WIDHT 1600
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Enternity Engine, Version:0.0003, Author:lvke"

void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		//LOG_INFO(std::to_string(key) + " release");
		InputEventManager::GetInstance().NotifyKeyRelease((Enternity::Keyboard)key);
	}

	if (action == GLFW_PRESS)
	{
		//LOG_INFO(std::to_string(key) + " press");
		InputEventManager::GetInstance().NotifyKeyPress((Enternity::Keyboard)key);
	}
}

void MouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		//LOG_INFO(std::to_string(button) + " release");
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		InputEventManager::GetInstance().NotifyMouseRelease({ (MouseButton)button, (int)x, (int)y, 0 });
	}

	if (action == GLFW_PRESS)
	{
		//LOG_INFO(std::to_string(button) + " press");
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		InputEventManager::GetInstance().NotifyMousePress({ (MouseButton)button, (int)x, (int)y, 0 });
	}
}

void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
{
	//LOG_INFO("mouse pos:" + std::to_string(xpos) + "," + std::to_string(ypos));
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		InputEventManager::GetInstance().NotifyMouseMove({ (MouseButton)GLFW_MOUSE_BUTTON_LEFT, (int)xpos, (int)ypos, 0 });
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		InputEventManager::GetInstance().NotifyMouseMove({ (MouseButton)GLFW_MOUSE_BUTTON_RIGHT, (int)xpos, (int)ypos, 0 });
	}
}


void MouseScrollEnvent(GLFWwindow* window, double xoffset, double yoffset)
{
	InputEventManager::GetInstance().NotifyMouseWheel({ (MouseButton)GLFW_MOUSE_BUTTON_MIDDLE, 0, 0, (int)yoffset * 10 });
}

Engine::~Engine()
{
	SAFE_DELETE_SET_NULL(m_framebuffer);
	ImguiManager::GetInstance().Release();
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
	glfwWindowHint(GLFW_SAMPLES, 4);

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

	//antialiasing
	glEnable(GL_MULTISAMPLE);
	//blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//depth tes
	glEnable(GL_DEPTH_TEST);

	//viewport
	glViewport(0, 0, WINDOW_WIDHT, WINDOW_HEIGHT);


	//framebuffer
	m_framebuffer = new FrameBuffer(WINDOW_WIDHT, WINDOW_HEIGHT);

	//hardware info
	LOG_INFO((char*)glGetString(GL_VERSION));
	LOG_INFO((char*)glGetString(GL_VENDOR));
	LOG_INFO((char*)glGetString(GL_RENDERER));

	//all kinds of callback	
	glfwSetKeyCallback(m_context, KeyEvent);
	glfwSetMouseButtonCallback(m_context, MouseButtonEvent);
	glfwSetCursorPosCallback(m_context, MouseMoveEvent);
	glfwSetScrollCallback(m_context, MouseScrollEnvent);

	ImguiManager::GetInstance().Initialize(m_context);
	SceneManager::GetInstance().Initialize();
	
	LOG_INFO("Engine initialization is complete");

	return true;
}

void Engine::Run()
{
	while (!glfwWindowShouldClose(m_context) && !m_userNeedShutDown)
	{
		//render to my framebuffer
		{
			m_framebuffer->Bind();

			//clear
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//tick event,  The unit of deltaTime is second
			ImGuiIO& io = ImGui::GetIO();
			if(io.Framerate)
				TickEventManager::GetInstance().NotifyTick(1.0f / io.Framerate);

			//scene
			if (io.Framerate)
				SceneManager::GetInstance().Tick(1.0f / io.Framerate);

			m_framebuffer->Resolve();
		}

		//render imgui to screen or window
		{
			//imgui
			m_framebuffer->UnBind();
			//clear
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ImguiManager::GetInstance().Draw();
		}

		glfwSwapBuffers(m_context);
		glfwPollEvents();
	}
}

void Engine::ShutDown()
{
	m_userNeedShutDown = true;
}

//imgui viewport resize
void Engine::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
	
	if (width <= 0 || height <= 0)
		return;
	
	SceneManager::GetInstance().OnResize(width, height);

	m_framebuffer->Rebuild(width, height);

	LOG_INFO("Resize:" + std::to_string(width) + "," + std::to_string(height));
}

float Engine::GetDeltaTime()
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.Framerate)
		return 1.0f / io.Framerate;
	return 0.0f;
}

GLFWwindow* Engine::GetContext()
{
	return m_context;
}

END_ENTERNITY