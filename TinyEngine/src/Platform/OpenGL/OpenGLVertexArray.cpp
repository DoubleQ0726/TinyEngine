#include "TinyPch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace TinyEngine
{
	static GLenum ShaderDataTypeToOPenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case TinyEngine::ShaderDataType::Float:		return GL_FLOAT;
		case TinyEngine::ShaderDataType::Float2:	return GL_FLOAT;
		case TinyEngine::ShaderDataType::Float3:	return GL_FLOAT;
		case TinyEngine::ShaderDataType::Float4:	return GL_FLOAT;
		case TinyEngine::ShaderDataType::Mat3:		return GL_FLOAT;
		case TinyEngine::ShaderDataType::Mat4:		return GL_FLOAT;
		case TinyEngine::ShaderDataType::Int:		return GL_INT;
		case TinyEngine::ShaderDataType::Int2:		return GL_INT;
		case TinyEngine::ShaderDataType::Int3:		return GL_INT;
		case TinyEngine::ShaderDataType::Int4:		return GL_INT;
		case TinyEngine::ShaderDataType::Bool:		return GL_BOOL;
		default:
			break;
		}
		TI_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{

	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		TI_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (auto& element :vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOPenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}