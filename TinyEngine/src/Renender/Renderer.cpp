#include "TinyPch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace TinyEngine
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray, 
		const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetUniformMat4f("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetUniformMat4f("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}

}