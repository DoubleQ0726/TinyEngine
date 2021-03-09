#include "TinyPch.h"
#include "OpenGLContext.h"
#include "Tiny/Core.h"
#include "Tiny/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TinyEngine
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		TI_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TI_CORE_ASSERT(status, "Failed to initalize Glad!");

		TI_CORE_INFO("OpenGL Renderer: {0} {1} {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}