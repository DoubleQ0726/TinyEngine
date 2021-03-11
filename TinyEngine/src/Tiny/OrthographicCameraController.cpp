#include "TinyPch.h"
#include "OrthographicCameraController.h"
#include "Tiny/Input.h"
#include "Tiny/KeyCodes.h"
#include "Tiny/Core.h"

namespace TinyEngine
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRation(aspectRatio), 
		m_Camera(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), 
		m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(TINY_KEY_A))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		else if (TinyEngine::Input::IsKeyPressed(TINY_KEY_D))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(TINY_KEY_W))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(TINY_KEY_S))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(TINY_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(TINY_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(TI_BIND_EVENT_FN(OrthographicCameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(TI_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScroll(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjectionMatrix(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetHeight() == 0)
			return false;
		m_AspectRation = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjectionMatrix(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}