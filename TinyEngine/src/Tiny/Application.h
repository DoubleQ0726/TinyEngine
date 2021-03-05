#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace TinyEngine
{
	class TINY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in Client
	Application* CreateApplication();
}

