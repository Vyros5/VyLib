#pragma once

#include "VyLib/Containers/Streams.h"

namespace Vy
{
    template <typename T>
    class Bitmask
    {
    public:
		Bitmask()  = default;
		~Bitmask() = default;

        Bitmask(T mask) :
            m_Mask(mask)
        {
        }

        VYINLINE bool IsSet(T mask) const
        {
            return (m_Mask & mask) != 0;
        }

        VYINLINE bool IsAllSet(T bits) const
        {
            return (m_Mask & bits) == bits;
        }

        VYINLINE void Set(T mask)
        {
            m_Mask |= mask;
        }

        VYINLINE void Set(T mask, bool isSet)
        {
            if (isSet)
                m_Mask |= mask;
            else
                m_Mask &= ~mask;
        }

        VYINLINE void Remove(T mask)
        {
            m_Mask &= ~mask;
        }

        VYINLINE T GetValue() const
        {
            return m_Mask;
        }

		void SaveToStream(OStream& stream) const
		{
			stream << m_Mask;
		}

		void LoadFromStream(IStream& stream)
		{
			stream >> m_Mask;
		}
    
    private:

        T m_Mask = 0;
    };

    typedef Bitmask<u8>  Bitmask8;
    typedef Bitmask<u16> Bitmask16;
    typedef Bitmask<u32> Bitmask32;
}