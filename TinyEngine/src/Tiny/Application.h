#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Tiny/LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renender/Shader.h"
#include "Renender/OrthographicCamera.h"

namespace TinyEngine
{
	class TINY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);

		void Run();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);

		static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		std::shared_ptr<Shader> m_ShaderA;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_ShaderB;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	//To be defined in Client
	Application* CreateApplication();
}

