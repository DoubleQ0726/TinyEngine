#pragma once
#include "Tiny.h"
#include "Tiny/Core/Layer.h"

class SandBox2D : public TinyEngine::Layer
{
public:
	SandBox2D();
	virtual ~SandBox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(TinyEngine::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(TinyEngine::Event& e) override;

private:
	TinyEngine::Ref<TinyEngine::Shader> m_Shader;
	TinyEngine::Ref<TinyEngine::VertexArray> m_SquareVA;
	TinyEngine::OrthographicCameraController m_CameraController;
	TinyEngine::Ref<TinyEngine::Texture2D> m_ChernoLogoTexture;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
