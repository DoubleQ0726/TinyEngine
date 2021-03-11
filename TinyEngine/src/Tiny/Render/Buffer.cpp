#include "TinyPch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Tiny/Core/Core.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace TinyEngine
{
	
	TinyEngine::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
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
				return new TinyEngine::OpenGLVertexBuffer(vertices, size);
			}
			default:
				break;
		}
		TI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	TinyEngine::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
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
			return new TinyEngine::OpenGLIndexBuffer(indices, count);
		}
		default:
			break;
		}
		TI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}