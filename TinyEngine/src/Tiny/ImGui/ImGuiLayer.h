#pragma once
#include "Tiny/Core/Layer.h"
#include "Tiny/Events/MouseEvent.h"
#include "Tiny/Events/KeyEvent.h"
#include "Tiny/Events/ApplicationEvent.h"
namespace TinyEngine
{
	class TINY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
