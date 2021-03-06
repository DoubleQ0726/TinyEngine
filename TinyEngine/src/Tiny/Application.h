#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Tiny/LayerStack.h"

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

	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in Client
	Application* CreateApplication();
}

