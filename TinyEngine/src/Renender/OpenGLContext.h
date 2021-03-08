#pragma once
#include "GraphicsContext.h"
struct GLFWwindow;

namespace TinyEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		void Init() override;
		void SwapBuffers() override;


	private:
		GLFWwindow* m_windowHandle;
	};
}