#pragma once

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Types/StringTypes.h"
#include "VyLib/Types/DefTypes.h"

#include "VyLib/Containers/Array.h"
#include "VyLib/Utils/EnumUtils.h"

namespace Vy
{
    /**
     * 
     * 
     * 
     */

    enum  EventType
    {
        NONE = 0,

        WINDOW_CLOSE,
        WINDOW_RESIZE,
        WINDOW_FOCUSED,
        WINDOW_LOST_FOCUS,
        WINDOW_MOVED,

        APP_TICK,
        APP_UPDATE,
        APP_RENDER,

        KEY_PRESSED,
        KEY_RELEASED,
        KEY_TYPED,

        MOUSE_BUTTON_PRESSED,
        MOUSE_BUTTON_RELEASED,
        MOUSE_MOVED,
        MOUSE_SCROLLED,
    };


    enum class EventCategory
    {
        NONE         = 0,

        APPLICATION  = VY_BIT(0), // 1
        INPUT        = VY_BIT(1), // 2
        KEYBOARD     = VY_BIT(2), // 4
        MOUSE        = VY_BIT(3), // 8
        MOUSE_BUTTON = VY_BIT(4)  // 16
    };

    DECLARE_FLAGS(EventCategory);

#define EVENT_CLASS_TYPE(type, ...)                                              \
    static  EventType GetStaticType()                { return EventType::type; } \
    virtual EventType GetEventType()  const override { return GetStaticType(); } \
    virtual cstring   GetName()       const override { return #type; }          // 
    // virtual cstring   GetCSharpCtor() const override { return "Eagle." #type "Event:.ctor " "(" #__VA_ARGS__ ")"; }

#define EVENT_CLASS_CATEGORY(category)                                           \
    virtual EventCategory GetCategoryFlags() const override { return category; }


	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		VYNODISCARD virtual EventType       GetEventType()     const = 0;
		VYNODISCARD virtual cstring         GetName()          const = 0;
		VYNODISCARD virtual cstring         GetCSharpCtor()    const = 0;
		VYNODISCARD virtual EventCategory   GetCategoryFlags() const = 0;
		VYNODISCARD virtual String          ToString()         const { return GetName(); }
		VYNODISCARD virtual Array<void*, 2> GetData()                { return { nullptr, nullptr }; }

		VYNODISCARD bool IsInCategory(EventCategory category) const noexcept
		{
			return (GetCategoryFlags() & category) == category;
		}
	};


	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : 
            m_Event(event) 
        {
        }

		//F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};


	VYINLINE std::ostream& operator<< (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}