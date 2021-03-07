#include "TinyPch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
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

		TI_CORE_TRACE(e);

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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			m_Window->OnUpdate();
		}
	}
}