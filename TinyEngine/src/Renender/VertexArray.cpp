#include "TinyPch.h"
#include "VertexArray.h"
#include "Renender/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace TinyEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
		{
			TI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}
		case RendererAPI::OpenGL:
		{
			return new TinyEngine::OpenGLVertexArray();
		}
		default:
			break;
		}
		TI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}