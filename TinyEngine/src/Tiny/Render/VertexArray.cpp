#include "TinyPch.h"
#include "VertexArray.h"
#include "Tiny/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace TinyEngine
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			TI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return std::make_shared<OpenGLVertexArray>();
		}
		default:
			break;
		}
		TI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}