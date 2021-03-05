#include "TinyPch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
namespace TinyEngine
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}
	
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			TI_TRACE(e);
		}
		while (true)
		{

		}
	}
}