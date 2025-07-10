#pragma once

#include "VyLib/Event/Event.h"
#include "VyLib/Input/InputCodes.h"
#include <sstream>

namespace Vy
{
	class MouseEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory::INPUT | EventCategory::MOUSE)
	protected:
		MouseEvent() = default;
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		EVENT_CLASS_TYPE(MOUSE_MOVED, f32, f32)

		MouseMovedEvent(f32 x, f32 y) : 
            m_MouseX(x), 
            m_MouseY(y) 
        {
        }

		f32 GetX() const { return m_MouseX; }
		f32 GetY() const { return m_MouseY; }

		VYNODISCARD String ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		Array<void*, 2> GetData() override { return { &m_MouseX, &m_MouseY }; }

	private:
		f32 m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public MouseEvent
	{
	public:
		EVENT_CLASS_TYPE(MOUSE_SCROLLED, f32, f32)

		MouseScrolledEvent(f32 xOffset, f32 yOffset) : 
            m_XOffset(xOffset), 
            m_YOffset(yOffset) 
        {
        }

		f32 GetXOffset() const { return m_XOffset; }
		f32 GetYOffset() const { return m_YOffset; }

		VYNODISCARD String ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		Array<void*, 2> GetData() override { return { &m_XOffset, &m_YOffset }; }

	private:
		f32 m_XOffset, m_YOffset;
	};


	class MouseButtonEvent : public MouseEvent
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory::INPUT | EventCategory::MOUSE | EventCategory::MOUSE_BUTTON)
	
		Mouse GetMouseCode() const { return m_MouseCode; }

	protected:
		MouseButtonEvent(Mouse mouseCode) : 
            m_MouseCode(mouseCode) 
        {
        }

		Mouse m_MouseCode;
	};


	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)

		MouseButtonPressedEvent(Mouse mouseCode) : 
            MouseButtonEvent(mouseCode) 
        {
        }

		VYNODISCARD String ToString() const override
		{
            return String("MouseButtonPressedEvent");
			// return String("MouseButtonPressedEvent: ") + Utils::GetEnumName(m_MouseCode);
		}

		Array<void*, 2> GetData() override { return { &m_MouseCode, nullptr }; }
	};


	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)

		MouseButtonReleasedEvent(Mouse mouseCode)
			: MouseButtonEvent(mouseCode) {}

		VYNODISCARD String ToString() const override
		{
            return String("MouseButtonReleasedEvent");
			// return String("MouseButtonReleasedEvent: ") + Utils::GetEnumName(m_MouseCode);
		}

		Array<void*, 2> GetData() override { return { &m_MouseCode, nullptr }; }
	};
}