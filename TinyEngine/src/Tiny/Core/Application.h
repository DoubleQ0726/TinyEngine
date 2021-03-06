#pragma once
#include "Core.h"
#include "Tiny/Events/Event.h"
#include "Window.h"
#include "Tiny/Events/ApplicationEvent.h"
#include "Tiny/Core/LayerStack.h"
#include "Tiny/ImGui/ImGuiLayer.h"
#include "Tiny/Core/Timestep.h"


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
		bool OnWindowResize(WindowResizeEvent& e);

		static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in Client
	Application* CreateApplication();
}

