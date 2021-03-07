#pragma once
#include "Event.h"

namespace TinyEngine
{
	class TINY_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeybord | EventCategoryInput)

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class TINY_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() { return m_RepeatCount; }

		/* implements */
		/*static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "KeyPressed"; }*/

		EVENT_CLASS_TYPE(KeyPressed)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << ")repeats";
			return ss.str();
		}
	private:
		int m_RepeatCount;
	};

	class TINY_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class TINY_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KeyTyped)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
	};
}
