#include "Engine.h"
#include "Log/Log.h"
#include "Imgui/ImguiManager.h"
#include "Event/InputEventManager.h"
#include "Event/TickEventManager.h"
#include "Scene/SceneManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

BEGIN_ENTERNITY

#define WINDOW_WIDHT 1800
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
	SAFE_DELETE_SET_NULL(m_framebufferEx);
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
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
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

	//depth test
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	//stencil test
	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_EQUAL, 1, 0xFF);

	//cull face
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

	//viewport
	glViewport(0, 0, WINDOW_WIDHT, WINDOW_HEIGHT);


	//framebuffer
	FrameBufferSpecification fbs;
	fbs.m_Width = WINDOW_WIDHT;
	fbs.m_Height = WINDOW_WIDHT;
	fbs.m_FBAS = FrameBufferAttachmentSpecification({FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::DEPTH24STENCIL8});
	m_framebufferEx = new FrameBufferEx(fbs);

	//hardware info
	LOG_INFO((char*)glGetString(GL_VERSION));
	LOG_INFO((char*)glGetString(GL_VENDOR));
	LOG_INFO((char*)glGetString(GL_RENDERER));

	//all kinds of callback	
	glfwSetKeyCallback(m_context, KeyEvent);
	glfwSetMouseButtonCallback(m_context, MouseButtonEvent);
	glfwSetCursorPosCallback(m_context, MouseMoveEvent);
	glfwSetScrollCallback(m_context, MouseScrollEnvent);

	SceneManager::GetInstance().Initialize();
	ImguiManager::GetInstance().Initialize(m_context);
	
	LOG_INFO("Engine initialization is complete");

	return true;
}

void Engine::Run()
{
	while (!glfwWindowShouldClose(m_context) && !m_userNeedShutDown)
	{
		//render to my framebuffer
		{

			m_framebufferEx->Bind();

			//clear
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			//tick event,  The unit of deltaTime is second
			ImGuiIO& io = ImGui::GetIO();
			if(io.Framerate)
				TickEventManager::GetInstance().NotifyTick(1.0f / io.Framerate);

			//scene
			if (io.Framerate)
				SceneManager::GetInstance().Tick(1.0f / io.Framerate);

			//m_framebuffer->Resolve();
		}



		//render imgui to screen or window
		{
			//imgui
			m_framebufferEx->UnBind();
			////clear
			//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ImguiManager::GetInstance().Draw();
		}

		glfwSwapBuffers(m_context);
		glfwPollEvents();
	}

	//fix physicsSysten bug/crash (close the window when physics simulation)
	SceneManager::GetInstance().OnEditor();
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

	m_framebufferEx->ReSize(width, height);

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