#pragma once

#include "VyLib/Memory/Allocators/BaseAllocator.h"

namespace Vy::Memory
{
    class MallocAllocator : public IBaseAllocator
    {
    public:
		VY_FINLINE VoidPtr Allocate(SIZE_T size, SIZE_T alignment = 8)
		{
			return MallocAllocator::allocate(size, alignment);
		}

		VY_FINLINE bool Reallocate(VoidPtr ptr, SIZE_T size, SIZE_T alignment = 8)
		{
			return MallocAllocator::reallocate(ptr, size, alignment);
		}

		VY_FINLINE void Free(VoidPtr ptr, SIZE_T size = 0)
		{
			MallocAllocator::free(ptr, size);
		}

		// Used for smart ptrs
		static VoidPtr allocate(SIZE_T size, SIZE_T alignment = 8)
		{
			auto ptr = std::malloc(size);
			// VY_TRACEY_ALLOC(ptr, size);
			return ptr;
		}

		static bool reallocate(VoidPtr ptr, SIZE_T size, SIZE_T alignment = 8)
		{
			return false;
		}

		static void free(VoidPtr ptr, SIZE_T size = 0)
		{
			// VY_TRACEY_FREE(ptr);
			std::free(ptr);
		}
    };
}