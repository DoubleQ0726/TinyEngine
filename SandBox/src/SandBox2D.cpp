#include "SandBox2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController(4.0f / 3.0f)
{
	OnAttach();
}

void SandBox2D::OnAttach()
{
	m_ChernoLogoTexture = TinyEngine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(TinyEngine::Timestep ts)
{
	//TI_PROFILE_FUNCTION();

	//Update
	{
		//TI_PROFILE_SCOPE("CameraController::Update");
		m_CameraController.OnUpdate(ts);
	}

	//Render
	TinyEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	TinyEngine::RenderCommand::Clear();
	TinyEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	TinyEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, {0.8f, 0.2f, 0.3f, 1.0f});
	TinyEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
	TinyEngine::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, glm::radians(45.0f), m_ChernoLogoTexture, 10.0f);
	TinyEngine::Renderer2D::EndScene();
}

void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandBox2D::OnEvent(TinyEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}

