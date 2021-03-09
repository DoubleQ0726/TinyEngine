#include <Tiny.h>
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

class ExampleLayer : public TinyEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		float vertices[9] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		unsigned int indeices[3] =
		{
			0, 1, 2
		};
		m_ShaderA = std::make_unique<TinyEngine::Shader>("D:\\Work\\C++\\TinyEngine\\TinyEngine\\res\\shaders\\Basic.Shader");
		m_ShaderB = std::make_unique<TinyEngine::Shader>("D:\\Work\\C++\\TinyEngine\\TinyEngine\\res\\shaders\\ShaderB.shader");
		std::shared_ptr<TinyEngine::VertexBuffer> vertexBuffer;
		std::shared_ptr<TinyEngine::IndexBuffer> indexBuffer;
		m_VertexArray.reset(TinyEngine::VertexArray::Create());
		vertexBuffer.reset(TinyEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		TinyEngine::BufferLayout layout = {
			{TinyEngine::ShaderDataType::Float3, "a_Poaition"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(TinyEngine::IndexBuffer::Create(indeices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		float squareVertices[3 * 4] =
		{
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		m_SquareVA.reset(TinyEngine::VertexArray::Create());
		TinyEngine::BufferLayout squareVBLayout = {
			{TinyEngine::ShaderDataType::Float3, "position"},
		};
		std::shared_ptr<TinyEngine::VertexBuffer> squareVB;
		squareVB.reset(TinyEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(squareVBLayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = {
			0, 1, 3,
			1, 2, 3 };
		std::shared_ptr<TinyEngine::IndexBuffer> squareIB;
		squareIB.reset(TinyEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);
	}

	void OnUpdate(TinyEngine::Timestep ts) override
	{
		TI_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMillisecond());
		if (TinyEngine::Input::IsKeyPressed(TINY_KEY_LEFT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		else if (TinyEngine::Input::IsKeyPressed(TINY_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (TinyEngine::Input::IsKeyPressed(TINY_KEY_UP))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (TinyEngine::Input::IsKeyPressed(TINY_KEY_DOWN))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (TinyEngine::Input::IsKeyPressed(TINY_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		if (TinyEngine::Input::IsKeyPressed(TINY_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		if (TinyEngine::Input::IsKeyPressed(TINY_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (TinyEngine::Input::IsKeyPressed(TINY_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		if (TinyEngine::Input::IsKeyPressed(TINY_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (TinyEngine::Input::IsKeyPressed(TINY_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		TinyEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		TinyEngine::RenderCommand::Clear();
		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);

		TinyEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0), pos) * scale;
				TinyEngine::Renderer::Submit(m_ShaderA, m_SquareVA, transform);
			}
		}
		//TinyEngine::Renderer::Submit(m_ShaderB, m_VertexArray);
		TinyEngine::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(TinyEngine::Event& e) override
	{
		TinyEngine::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<TinyEngine::KeyPressedEvent>(TI_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(TinyEngine::KeyPressedEvent& event)
	{
		return false;
	}

private:
	std::shared_ptr<TinyEngine::Shader> m_ShaderA;
	std::shared_ptr<TinyEngine::VertexArray> m_VertexArray;

	std::shared_ptr<TinyEngine::Shader> m_ShaderB;
	std::shared_ptr<TinyEngine::VertexArray> m_SquareVA;

	TinyEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_SquarePosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	float m_SquareMoveSpeed = 1.0f;
};

class SandBox : public TinyEngine::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}
};

TinyEngine::Application* TinyEngine::CreateApplication()
{
	return new SandBox();
}