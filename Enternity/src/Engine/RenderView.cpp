#include "RenderView.h"
#include "Log.h"
#include "Common/Macro.h"
#include "Editor/UiRender.h"
#include "Engine.h"
#include "Engine/Blob.h"
#include "Event/EventSystem.h"
#include "Graphics/RHI/Texture/TextureAsset.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enternity
{
	RenderView::RenderView(unsigned int width, unsigned int height, const char* title)
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

		m_context = glfwCreateWindow(width, height, title, nullptr, nullptr);
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
		CHECK_GL_CALL(glViewport(0, 0, width, height));

		//glfwSetWindowSizeCallback(m_context, Resize);
		glfwSetKeyCallback(m_context, KeyTrigger);
		glfwSetMouseButtonCallback(m_context, MouseTrigger);
		glfwSetCursorPosCallback(m_context, MouseMove);

		TextureAsset ta("assets/textures/logo/windowlogo.png", false);
		ta.load(0);
		if (ta.getLoadingState() == Asset::loading_state_succeeded)
		{
			GLFWimage images[1];
			images[0].pixels = (unsigned char*)ta.getBlob()->getData();
			images[0].width = ta.getWidth();
			images[0].height = ta.getHeight();
			glfwSetWindowIcon(m_context, 1, images);
		}


		LOG_INFO((char*)glGetString(GL_VERSION));
		LOG_INFO((char*)glGetString(GL_VENDOR));
		LOG_INFO((char*)glGetString(GL_RENDERER));

		m_uiRender = new UiRender(m_context);

		//Resize(m_context, width, height);
	}

	RenderView::~RenderView()
	{
		SAFE_DELETE_SET_NULL(m_uiRender);
		glfwTerminate();
	}

	bool RenderView::windowShouldClose()
	{
		return glfwWindowShouldClose(m_context);
	}

	void RenderView::swapBuffers()
	{
		m_uiRender->tick();
		glfwSwapBuffers(m_context);
		glfwPollEvents();
	}

	void RenderView::setTitle(const char* title)
	{
		glfwSetWindowTitle(m_context, title);
	}

	void RenderView::Resize(GLFWwindow* window, int width, int height)
	{
		CHECK_GL_CALL(glViewport(0, 0, width, height));

		WindowSize ws{ width, height };
		Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::WindowResize, &ws);
	}

	void RenderView::Resize(int width, int height)
	{
		if (width <= 0 || height <= 0)
			return;

		LOG_INFO("ViewPortResize: width = " + std::to_string(width) + ", height = " + std::to_string(height));

		CHECK_GL_CALL(glViewport(0, 0, width, height));

		WindowSize ws{ width, height };
		Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::WindowResize, &ws);
	}

	void RenderView::KeyTrigger(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::KeyPressed, &key);
		}
		else if (action == GLFW_RELEASE)
		{
			Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::KeyReleased, &key);
		}
	}

	void RenderView::MouseTrigger(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);

			Mouse mouse{ (MouseCode)button,(float)x, (float)y };
			Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::MousePressed, &mouse);
		}

		if (action == GLFW_RELEASE)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);

			Mouse mouse{ (MouseCode)button,(float)x, (float)y };
			Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::MouseReleased, &mouse);
		}
	}

	void RenderView::MouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);

			Mouse mouse{ MouseCode::ButtonLeft,(float)x, (float)y };
			Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::MouseMoved, &mouse);
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(window, &x, &y);

			Mouse mouse{ MouseCode::ButtonRight,(float)x, (float)y };
			Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::MouseMoved, &mouse);
		}
	}
}