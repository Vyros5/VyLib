#pragma once

#include "VyLib/Event/Event.h"

#include <sstream>

namespace Vy
{
	class WindowResizeEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory::APPLICATION)
		EVENT_CLASS_TYPE(WINDOW_RESIZE, u32, u32)

		WindowResizeEvent(u32 width, u32 height) : 
            m_Width(width), 
            m_Height(height) 
        {
        }

		u32 GetWidth() const { return m_Width; }
		u32 GetHeight() const { return m_Height; }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		Array<void*, 2> GetData() override { return { &m_Width, &m_Height }; }

	private:
		u32 m_Width, m_Height;
	};


	class WindowCloseEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory::APPLICATION)
		EVENT_CLASS_TYPE(WINDOW_CLOSE)

		WindowCloseEvent() = default;
	};


	class WindowFocusedEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory::APPLICATION)
		EVENT_CLASS_TYPE(WINDOW_FOCUSED, bool)

		WindowFocusedEvent(bool focused) : 
            m_Focused(focused) 
        {
        }

		bool IsFocused() const { return m_Focused; }

		String ToString() const override
		{
			return m_Focused ? "WindowFocusedEvent: true" : "WindowFocusedEvent: false";
		}

		Array<void*, 2> GetData() override { return { &m_Focused, nullptr }; }

	private:
		bool m_Focused;
	};
}