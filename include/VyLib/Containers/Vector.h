#pragma once

#include <vector>
#include <memory>

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Prerequisites.h"

namespace Vy
{
    /* A sequence container that encapsulates dynamic size arrays / resizable contiguous array */
    
    template <typename T, typename TAllocator = std::allocator<T>> 
    using Vector = std::vector<T, TAllocator>;


    namespace VecUtil
    {
        template <typename T>
        VYINLINE i32 IndexOf(const Vy::Vector<T>& vec, const T& value)
        {
            const i32 sz = static_cast<i32>(vec.size());

            for (i32 i = 0; i < sz; ++i)
            {
                if (vec[i] == value)
                {
                    return i;
                }
            }

            return -1;
        }


        template <typename T>
        VYINLINE i32 FindNextIndexIfItemIsRemoved(const Vy::Vector<T>& vec, const T& value)
        {
			const i32 currentIndex = IndexOf(vec, value);

			if (currentIndex == 0)
			{
				if (vec.size() == 1)
                {
                    return -1;
                }

				return 0;
			}

			return currentIndex - 1;
        }


        template <typename T>
        VYINLINE void PlaceAfter(Vy::Vector<T>& vec, T& src, T& target)
        {
            auto itSrc = std::find_if(vec.begin(), vec.end(), [src](const T& child)    { return child == src; });
            auto itTar = std::find_if(vec.begin(), vec.end(), [target](const T& child) { return child == target; });

            vec.erase(itSrc);
            vec.insert(itTar + 1, *itSrc);
        }


        template <typename T>
        VYINLINE void PlaceBefore(Vy::Vector<T>& vec, const T& src, const T& target)
        {
            auto itSrc = std::find_if(vec.begin(), vec.end(), [src](const T& child)    { return child == src; });
            auto itTar = std::find_if(vec.begin(), vec.end(), [target](const T& child) { return child == target; });

            vec.insert(itTar, *itSrc);
            if (itSrc < itTar)
            {
                vec.erase(itSrc);
            }
            else
            {
                vec.erase(itSrc + 1);
            }
        }


        template <typename T>
        VYINLINE bool Contains(const Vy::Vector<T>& vec, const T& data)
        {
			for (const auto& v : vec)
			{
				if (v == data)
                {
                    return true;
                }
			}

			return false;
        }
    }
}
