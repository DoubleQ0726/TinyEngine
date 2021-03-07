#include "TinyPch.h"
#include "WindowsInput.h"
#include "Tiny/Application.h"
#include <GLFW/glfw3.h>

namespace TinyEngine
{
	Input* Input::s_instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto status =  glfwGetKey(window, keycode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto status = glfwGetMouseButton(window, button);
		return status == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		//C++11
		/*auto pair = GetMousePositionImpl();
		return std::get<0>(pair);*/

		//C++17
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return std::make_pair((float)xPos, (float)yPos);
	}

}