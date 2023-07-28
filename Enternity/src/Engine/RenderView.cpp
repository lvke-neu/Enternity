#include "RenderView.h"
#include "Log.h"
#include "Engine.h"
#include "EventSystem.h"
#include "Blob.h"
#include "BlobLoader.h"
#include "Graphics/RHI/Texture/TextureBlobHolder.h"
#include "BlobLoaderManager.h"
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
		glfwSetScrollCallback(m_context, MouseScroll);

		LOG_INFO((char*)glGetString(GL_VERSION));
		LOG_INFO((char*)glGetString(GL_VENDOR));
		LOG_INFO((char*)glGetString(GL_RENDERER));

		//Resize(m_context, width, height);
	}

	RenderView::~RenderView()
	{
		glfwTerminate();
	}

	bool RenderView::windowShouldClose()
	{
		return glfwWindowShouldClose(m_context);
	}

	void RenderView::swapBuffers()
	{
		glfwSwapBuffers(m_context);
	}

	void RenderView::setTitle(const char* title)
	{
		glfwSetWindowTitle(m_context, title);
	}

	void RenderView::pollEvents()
	{
		glfwPollEvents();
	}

	void RenderView::setWindowProperty(unsigned int width, unsigned int height, const char* title, const char* path)
	{
		glfwSetWindowSize(m_context, width, height);
		glfwSetWindowTitle(m_context, title);

		BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
		if (blobLoader)
		{
			Texture2DBlobHolder* texture2DBlobHolder = dynamic_cast<Texture2DBlobHolder*>(blobLoader->createBlobHolder(path));
			if (texture2DBlobHolder)
			{
				texture2DBlobHolder->setSlip(false);
				texture2DBlobHolder->load(0);
				if (texture2DBlobHolder->isLoadSucceeded())
				{
					GLFWimage images[1];
					images[0].pixels = (unsigned char*)texture2DBlobHolder->getBlob()->getData();
					images[0].width = texture2DBlobHolder->getWidth();
					images[0].height = texture2DBlobHolder->getHeight();
					glfwSetWindowIcon(m_context, 1, images);
				}

				SAFE_DELETE_SET_NULL(texture2DBlobHolder);
			}
		}
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

		m_width = width;
		m_height = height;

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
	void RenderView::MouseScroll(GLFWwindow * window, double xoffset, double yoffset)
	{
		float delta = (float)yoffset;
		Engine::GetInstance().getEventSystem()->dispatchEvent(Event::EventType::MouseScroll, &delta);
	}
}