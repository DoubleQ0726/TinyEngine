#include "TinyPch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Tiny/Render/RenderCommand.h"
#include "glm/gtc/matrix_transform.hpp"

namespace TinyEngine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data = new Renderer2DStorage();


	void Renderer2D::Init()
	{

		float squareVertices[] =
		{
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		uint32_t squareIndices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		s_Data->QuadVertexArray = VertexArray::Create();
		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{TinyEngine::ShaderDataType::Float3, "a_Position"},
			{TinyEngine::ShaderDataType::Float2, "a_Texture"}
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(squareIndices, 6));
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->Set1i("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4f("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->TextureShader->Bind();
		//Bind white texture here
		s_Data->WhiteTexture->Bind(0);
		s_Data->TextureShader->Set4f("u_Color", color.r, color.g, color.b, color.a);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4f("u_Transform", transform);

		s_Data->TextureShader->Bind();
		RenderCommand::DrawIndex(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->Set4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		s_Data->TextureShader->Set1f("u_TilingFactor", tilingFactor);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4f("u_Transform", transform);

		texture->Bind(0);

		s_Data->TextureShader->Bind();
		RenderCommand::DrawIndex(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		s_Data->TextureShader->Bind();
		//Bind white texture here
		s_Data->WhiteTexture->Bind(0);
		s_Data->TextureShader->Set4f("u_Color", color.r, color.g, color.b, color.a);
		s_Data->TextureShader->Set1f("u_TilingFactor", 1.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * 
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4f("u_Transform", transform);

		s_Data->TextureShader->Bind();
		RenderCommand::DrawIndex(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, 
		const Ref<Texture2D>& texture, float tilingFactor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, 
		const Ref<Texture2D>& texture, float tilingFactor)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->Set4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		s_Data->TextureShader->Set1f("u_TilingFactor", tilingFactor);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * 
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4f("u_Transform", transform);

		texture->Bind(0);

		s_Data->TextureShader->Bind();
		RenderCommand::DrawIndex(s_Data->QuadVertexArray);
	}

}