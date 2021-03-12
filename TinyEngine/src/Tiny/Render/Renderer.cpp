#include "TinyPch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Tiny/Render/Renderer2D.h"

namespace TinyEngine
{
	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, 
		const Ref<VertexArray>& vertexArray, 
		const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4f("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4f("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}

}