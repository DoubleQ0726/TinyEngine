#pragma once
#include "Tiny/Render/OrthographicCamera.h"
#include "Tiny/Core/Timestep.h"
#include "Tiny/Events/ApplicationEvent.h"
#include "Tiny/Events/MouseEvent.h"
#include "glm/glm.hpp"

namespace TinyEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

	private:
		bool OnMouseScroll(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


	private:
		float m_AspectRation;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}
