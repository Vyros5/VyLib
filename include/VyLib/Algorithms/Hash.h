#pragma once

#include <functional>

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Types/StringTypes.h"

namespace Vy
{
    template<typename T>
    void HashCombine(SIZE_T& seed, const T& v);

    template<typename T, typename... Args>
    SIZE_T HashCombine(const T& v, const Args&... args);

    template<typename T>
    struct HashFunctor
    {
        template<typename... Args> 
        SIZE_T operator()(Args&&... args);
    };

    // ==================================================================================

    // Cyclic Redundancy Check (CRC) - 32bits
    constexpr u32 CRC32(cstring str) noexcept;
	constexpr u32 CRC32(StringView str) noexcept;
	constexpr u32 CRC32(const u8* data, SIZE_T size) noexcept;

	template<SIZE_T N> 
    constexpr u32 CRC32(const char(&str)[N]) noexcept;

    struct CRC32Hash
    {
        template<typename... Args>
        u32 operator()(Args&&... args);
    };

    // ==================================================================================

    // Fowler–Noll–Vo (FNV) 1a - 32bits
	constexpr u32 FNV1a32(cstring str) noexcept;
	constexpr u32 FNV1a32(StringView str) noexcept;
	constexpr u32 FNV1a32(const u8* data, SIZE_T size) noexcept;
	
    template<SIZE_T N> 
    constexpr u32 FNV1a32(const char(&str)[N]) noexcept;

	struct FNV1a32Hash
	{
		template<typename... Args> 
        u32 operator()(Args&&... args);
	};

    // ==================================================================================

	// Fowler–Noll–Vo (FNV) 1a - 64bits
	constexpr u64 FNV1a64(cstring str) noexcept;
	constexpr u64 FNV1a64(StringView str) noexcept;
	constexpr u64 FNV1a64(const u8* data, SIZE_T size) noexcept;
	template<SIZE_T N> 
    constexpr u64 FNV1a64(const char(&str)[N]) noexcept;

	struct FNV1a64Hash
	{
		template<typename... Args> 
        u64 operator()(Args&&... args);
	};
}

#include "Algorithms/Hash.inl"