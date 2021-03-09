#include "TinyPch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace TinyEngine
{
	RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();
}