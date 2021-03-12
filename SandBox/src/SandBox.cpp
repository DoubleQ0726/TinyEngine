#include <Tiny.h>
#include <Tiny/Core/EntryPoint.h>
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "SandBox2D.h"

class ExampleLayer : public TinyEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(4.0f / 3.0f, true), m_SquarePosition(0.0f)
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
		m_ShaderA = TinyEngine::Shader::Create("D:\\Work\\C++\\TinyEngine\\TinyEngine\\res\\shaders\\Basic.Shader");
		m_ShaderB = TinyEngine::Shader::Create("D:\\Work\\C++\\TinyEngine\\TinyEngine\\res\\shaders\\ShaderB.shader");
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		TinyEngine::Ref<TinyEngine::VertexBuffer> vertexBuffer;
		TinyEngine::Ref<TinyEngine::IndexBuffer> indexBuffer;
		m_VertexArray = TinyEngine::VertexArray::Create();
		vertexBuffer.reset(TinyEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		TinyEngine::BufferLayout layout = {
			{TinyEngine::ShaderDataType::Float3, "a_Poaition"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(TinyEngine::IndexBuffer::Create(indeices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		float squareVertices[] =
		{
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		m_SquareVA = TinyEngine::VertexArray::Create();
		TinyEngine::BufferLayout squareVBLayout = 
		{
			{TinyEngine::ShaderDataType::Float3, "a_Position"},
			{TinyEngine::ShaderDataType::Float2, "a_Texcoord"}
		};
		TinyEngine::Ref<TinyEngine::VertexBuffer> squareVB;
		squareVB.reset(TinyEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(squareVBLayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = 
		{
			0, 1, 3,
			1, 2, 3 
		};
		TinyEngine::Ref<TinyEngine::IndexBuffer> squareIB;
		squareIB.reset(TinyEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_Texture2D = TinyEngine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = TinyEngine::Texture2D::Create("assets/textures/ChernoLogo.png");
		textureShader->Bind();
		textureShader->Set1i("u_Texture", 0);
	}

	void OnUpdate(TinyEngine::Timestep ts) override
	{
		// OnUpdate
		m_CameraController.OnUpdate(ts);
		if (TinyEngine::Input::IsKeyPressed(TINY_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (TinyEngine::Input::IsKeyPressed(TINY_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		if (TinyEngine::Input::IsKeyPressed(TINY_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (TinyEngine::Input::IsKeyPressed(TINY_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;


		//Render
		TinyEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		TinyEngine::RenderCommand::Clear();
		TinyEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		m_ShaderA->Bind();
		m_ShaderA->Set4f("u_Color", m_SquareColor.r, m_SquareColor.g, m_SquareColor.b, m_SquareColor.a);
		for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0), pos) * scale;
				TinyEngine::Renderer::Submit(m_ShaderA, m_SquareVA, transform);
			}
		}
		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture2D->Bind(0);
		TinyEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind(0);
		TinyEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Triangle
		//TinyEngine::Renderer::Submit(m_ShaderB, m_VertexArray);
		TinyEngine::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(TinyEngine::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	bool OnKeyPressedEvent(TinyEngine::KeyPressedEvent& event)
	{
		return false;
	}

private:
	TinyEngine::ShaderLibrary m_ShaderLibrary;
	TinyEngine::Ref<TinyEngine::Shader> m_ShaderA;
	TinyEngine::Ref<TinyEngine::Shader> m_ShaderB;

	TinyEngine::Ref<TinyEngine::VertexArray> m_VertexArray;
	TinyEngine::Ref<TinyEngine::VertexArray> m_SquareVA;

	TinyEngine::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	TinyEngine::Ref<TinyEngine::Texture> m_Texture2D, m_ChernoLogoTexture;
};

class SandBox : public TinyEngine::Application
{
public:
	SandBox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new SandBox2D());
	}

	~SandBox()
	{

	}
};

TinyEngine::Application* TinyEngine::CreateApplication()
{
	return new SandBox();
}