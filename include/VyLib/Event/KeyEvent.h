#pragma once

#include "VyLib/Event/Event.h"
#include "VyLib/Input/InputCodes.h"
#include <sstream>

namespace Vy
{
	class KeyEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory::INPUT | EventCategory::KEYBOARD)

		Key GetKey() const { return m_KeyCode; }

	protected:
		KeyEvent(Key keyCode) : m_KeyCode(keyCode) {}
		
		Key m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KEY_PRESSED, u32)

		KeyPressedEvent(Key keyCode, u16 repeatCount) : 
            KeyEvent(keyCode), 
            m_RepeatCount(repeatCount) 
        {
        }

		uint32_t GetRepeatCount() const { return m_RepeatCount; }

		VYNODISCARD String ToString() const override
		{
            return String("KeyPressedEvent");
			// std::stringstream ss;
			// ss << "KeyPressedEvent: " << Utils::GetEnumName(m_KeyCode) << " (" << m_RepeatCount << " repeats)";
			// return ss.str();
		}

		Array<void*, 2> GetData() override { return { &m_KeyCode, &m_RepeatCount }; }

	private:
		uint32_t m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KEY_RELEASED)

		KeyReleasedEvent(Key keyCode)
			: KeyEvent(keyCode) {}

		VYNODISCARD String ToString() const override
		{
            return String("KeyReleasedEvent");
			// return String("KeyReleasedEvent: ") + Utils::GetEnumName(m_KeyCode);
		}

		Array<void*, 2> GetData() override { return { &m_KeyCode, nullptr }; }
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KEY_TYPED)

		KeyTypedEvent(Key keyCode)
			: KeyEvent(keyCode) {}

		VYNODISCARD String ToString() const override
		{
            return String("KeyTypedEvent");
			// return String("KeyTypedEvent: ") + Utils::GetEnumName(m_KeyCode);
		}
		
		Array<void*, 2> GetData() override { return { &m_KeyCode, nullptr }; }
	};
}