#pragma once
#include "Tiny/Window.h"
#include "Tiny/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TinyEngine
{
	class TINY_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		virtual void SetEventCallBack(const EventCallBackFn& callback) { m_Data.EventCallBack = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallBackFn EventCallBack;
		};
		WindowData m_Data;
	};
}
