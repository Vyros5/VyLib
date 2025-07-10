#include "Algorithms/Hash.h"

#include <array>

#include "VyLib/Platform.h"

namespace Vy
{
    namespace Detail
    {
		// https://stackoverflow.com/questions/28675727/using-crc32-algorithm-to-hash-string-at-compile-time
		// Generates CRC-32 table, algorithm based from this link:
		// http://www.hackersdelight.org/hdcodetxt/crc.c.txt
		constexpr auto GenerateCRC32Table(u32 polynomial = 0xEDB88320)
		{
VY_WARNING_PUSH()
VY_WARNING_MSVC_DISABLE(4146) // unary minus operator applied to unsigned type, result still unsigned

			constexpr u32 byteCount = 256;
			constexpr u32 iterationCount = 8;

			std::array<u32, byteCount> crc32Table{};
			for (u32 byte = 0u; byte < byteCount; ++byte)
			{
				u32 crc = byte;

				for (u32 i = 0; i < iterationCount; ++i)
				{
					u32 mask = static_cast<u32>(-(crc & 1));
					crc = (crc >> 1) ^ (polynomial & mask);
				}

				crc32Table[byte] = crc;
			}

			return crc32Table;

VY_WARNING_POP()
		}

		// Stores CRC-32 table and softly validates it.
		static constexpr auto s_crc32Table = GenerateCRC32Table();
		static_assert(
			s_crc32Table.size() == 256 &&
			s_crc32Table[1]     == 0x77073096 &&
			s_crc32Table[255]   == 0x2D02EF8D,
			"GenerateCRC32Table generated unexpected result."
		);

		constexpr u32 FNV1OffsetBasis_32 = 0x811c9dc5u;
		constexpr u32 FNV1Prime_32       = 0x1000193u;

		constexpr u64 FNV1OffsetBasis_64 = 0xcbf29ce484222325ull;
		constexpr u64 FNV1Prime_64       = 0x100000001b3ull;
    }


	// Algorithm from CityHash by Google
	// http://stackoverflow.com/questions/8513911/how-to-create-a-good-hash-combine-with-64-bit-output-inspired-by-boosthash-co

	/**
	* @brief Combines two hash in one
	*
	* @param seed First value that will be modified (expected to be 64bits)
	* @param v Second value to hash
    */
	template<typename T>
	void HashCombine(SIZE_T& seed, const T& v)
	{
		constexpr u64 kMul = 0x9ddfea08eb382d69ULL;

		std::hash<T> hasher;
		u64 a = (hasher(v) ^ seed) * kMul;
		a ^= (a >> 47);

		u64 b = (seed ^ a) * kMul;
		b ^= (b >> 47);

		seed = static_cast<SIZE_T>(b * kMul);
	}


	template<typename T, typename... Args>
	SIZE_T HashCombine(const T& v, const Args&... args)
	{
		SIZE_T hash = std::hash<T>{}(v);

		if constexpr (sizeof...(Args) > 0)
			HashCombine(hash, HashCombine(args...));

		return hash;
	}

	template<typename T>
	template<typename... Args>
	SIZE_T HashFunctor<T>::operator()(Args&&... args)
	{
		return static_cast<SIZE_T>(T{}(std::forward<Args>(args)...));
	}

    // ============================================================================================

	// From https://stackoverflow.com/questions/28675727/using-crc32-algorithm-to-hash-string-at-compile-time
	constexpr u32 CRC32(cstring str) noexcept
	{
		u32 crc = 0xFFFFFFFFu;

		for (SIZE_T i = 0u; str[i]; ++i)
			crc = Detail::s_crc32Table[(crc ^ str[i]) & 0xFF] ^ (crc >> 8);

		return ~crc;
	}

	constexpr u32 CRC32(StringView str) noexcept
	{
		u32 crc = 0xFFFFFFFFu;

		for (SIZE_T i = 0u; i < str.size(); ++i)
			crc = Detail::s_crc32Table[(crc ^ str[i]) & 0xFF] ^ (crc >> 8);

		return ~crc;
	}

	constexpr u32 CRC32(const u8* input, SIZE_T size) noexcept
	{
		u32 crc = 0xFFFFFFFFu;

		for (SIZE_T i = 0u; i < size; ++i)
			crc = Detail::s_crc32Table[(crc ^ input[i]) & 0xFF] ^ (crc >> 8);

		return ~crc;
	}

	template<SIZE_T N>
	constexpr u32 CRC32(const char(&str)[N]) noexcept
	{
		return CRC32(StringView(str, N));
	}

	template<typename... Args>
	u32 CRC32Hash::operator()(Args&&... args)
	{
		return CRC32(std::forward<Args>(args)...);
	}

    // ============================================================================================

	constexpr u32 FNV1a32(cstring str) noexcept
	{
		u32 hash = Detail::FNV1OffsetBasis_32;

		for (SIZE_T i = 0u; str[i]; ++i)
		{
			hash ^= u32(str[i]);
			hash *= Detail::FNV1Prime_32;
		}

		return hash;
	}

	constexpr u32 FNV1a32(StringView str) noexcept
	{
		u32 hash = Detail::FNV1OffsetBasis_32;

		for (SIZE_T i = 0u; i < str.size(); ++i)
		{
			hash ^= u32(str[i]);
			hash *= Detail::FNV1Prime_32;
		}

		return hash;
	}

	constexpr u32 FNV1a32(const u8* data, SIZE_T size) noexcept
	{
		u32 hash = Detail::FNV1OffsetBasis_32;

		for (SIZE_T i = 0u; i < size; ++i)
		{
			hash ^= data[i];
			hash *= Detail::FNV1Prime_32;
		}

		return hash;
	}

	template<SIZE_T N>
	constexpr u32 FNV1a32(const char(&str)[N]) noexcept
	{
		return FNV1a32(StringView(str, N));
	}

	template<typename... Args>
	u32 FNV1a32Hash::operator()(Args&&... args)
	{
		return FNV1a32(std::forward<Args>(args)...);
	}

    // ============================================================================================

	constexpr u64 FNV1a64(cstring str) noexcept
	{
		u64 hash = Detail::FNV1OffsetBasis_64;

		for (SIZE_T i = 0u; str[i]; ++i)
		{
			hash ^= u64(str[i]);
			hash *= Detail::FNV1Prime_64;
		}

		return hash;
	}

	constexpr u64 FNV1a64(StringView str) noexcept
	{
		u64 hash = Detail::FNV1OffsetBasis_64;

		for (SIZE_T i = 0u; i < str.size(); ++i)
		{
			hash ^= u64(str[i]);
			hash *= Detail::FNV1Prime_64;
		}

		return hash;
	}

	constexpr u64 FNV1a64(const u8* data, SIZE_T size) noexcept
	{
		u64 hash = Detail::FNV1OffsetBasis_64;

		for (SIZE_T i = 0u; i < size; ++i)
		{
			hash ^= data[i];
			hash *= Detail::FNV1Prime_64;
		}

		return hash;
	}

	template<SIZE_T N>
	constexpr u64 FNV1a64(const char(&str)[N]) noexcept
	{
		return FNV1a64(StringView(str, N));
	}

	template<typename... Args>
	u64 FNV1a64Hash::operator()(Args&&... args)
	{
		return FNV1a64(std::forward<Args>(args)...);
	}
}