#include "TinyPch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "Platform/Windows/WindowsInput.h"
#include "Renender/Renderer.h"
#include "Renender/RenderCommand.h"
namespace TinyEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) 
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		TI_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverLay(m_ImGuiLayer);

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
		m_ShaderA = std::make_unique<Shader>("D:\\Work\\C++\\TinyEngine\\TinyEngine\\res\\shaders\\Basic.Shader");
		m_ShaderB = std::make_unique<Shader>("D:\\Work\\C++\\TinyEngine\\TinyEngine\\res\\shaders\\ShaderB.shader");
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
		m_VertexArray.reset(VertexArray::Create());
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Poaition"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(IndexBuffer::Create(indeices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		float squareVertices[3 * 4] =
		{
			 0.5f,  0.5f, 0.0f,   
			 0.5f, -0.5f, 0.0f,  
			-0.5f, -0.5f, 0.0f, 
			-0.5f,  0.5f, 0.0f 
		};
		m_SquareVA.reset(VertexArray::Create());
		BufferLayout squareVBLayout = {
			{ShaderDataType::Float3, "position"},
		};
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(squareVBLayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 
			0, 1, 3, 
			1, 2, 3 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);
	}

	Application::~Application()
	{
		m_Running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//TI_CORE_TRACE(e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			if (e.m_Handle)
				break;
			(*(--it))->OnEvent(e);
		}

	}

	void Application::Run()
	{
		//WindowResizeEvent e(1280, 720);
		//if (e.IsInCategory(EventCategoryApplication))
		//{
		//	TI_TRACE(e);
		//}
		while (m_Running)
		{

			RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_ShaderA->Bind();
			Renderer::Submit(m_SquareVA);

			m_ShaderB->Bind();
			Renderer::Submit(m_VertexArray);
			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}