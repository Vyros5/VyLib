#pragma once

#include <cassert>
#include <cstdint>
#include <string>

#include "VyLib/Prerequisites.h"

/**
 * Fixed-Width Integer Types
 * https://en.cppreference.com/w/cpp/types/integer.html
 * 
 * Fundamental Types
 * https://en.cppreference.com/w/cpp/language/types.html
 * 
 * char      - Width of at least 8-bits.
 * int       - Width of at least 16-bits. (Is at least 32-bits on 32/64-bit Systems.)
 * short     - Width of at least 16-bits.
 * long      - Width of at least 32-bits.
 * long long - Width of at least 64-bits.
 */

// ================================================================================================
// UNSIGNED INTEGERS

/// @brief Unsigned 8-bit integer (unsigned char)
using u8  = std::uint8_t;

/// @brief Unsigned 16-bit integer (unsigned short)
using u16 = std::uint16_t;

/// @brief Unsigned 32-bit integer (unsigned int)
using u32 = std::uint32_t;

/// @brief Unsigned 64-bit integer (unsigned long long)
using u64 = std::uint64_t;

// ================================================================================================
// SIGNED INTEGERS

/// @brief Signed 8-bit integer (char)
using i8  = std::int8_t;

/// @brief Signed 16-bit integer (short)
using i16 = std::int16_t;

/// @brief Signed 32-bit integer (int)
using i32 = std::int32_t;

/// @brief Signed 64-bit integer (long long)
using i64 = std::int64_t;

// ================================================================================================
// FLOATING-POINTS

/// @brief 32-bit floating point number (float)
using f32 = float;

/// @brief 64-bit floating point number (double)
using f64 = double;

// ================================================================================================
// BOOLS

/// @brief 8-bit boolean
using b8  = bool;

// ================================================================================================
// CHARS

/// @brief Signed 8-bit char
using c8    = char;
using uchar = unsigned char;
using uc8   = unsigned char;
using c16   = char16_t;
using c32   = char32_t;

// ================================================================================================
// POINTERS

using IntPtr   = std::intptr_t;
using UintPtr  = std::uintptr_t;
using PtrDiff  = std::intptr_t;

using CharPtr  = char*;
using WCharPtr = wchar_t*;

using VoidPtr  = void*;
using CVoidPtr = const void*;

// ================================================================================================

#if VY_64BIT_SYSTEM
    using SIZE_T  = std::size_t;
    using SSIZE_T = i64;
#else
    using SIZE_T  = std::size_t;
    using SSIZE_T = i32;
#endif

// ================================================================================================

/// @brief Make Unsigned
using usize = std::make_unsigned_t<SIZE_T>;

/// @brief Make Signed
using isize = std::make_signed_t<SIZE_T>;

// ================================================================================================
// COMPILE-TIME ASSERTIONS

static_assert(sizeof(bool)          == 1);
static_assert(sizeof(char)          == 1);
static_assert(sizeof(float)         == 4);
static_assert(sizeof(double)        == 8);
static_assert(sizeof(long long int) == 8);

static_assert(sizeof(i8)  == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(i64) == 8);

static_assert(sizeof(u8)  == 1);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(u32) == 4);
static_assert(sizeof(u64) == 8);

static_assert(sizeof(f32) == 4);
static_assert(sizeof(f64) == 8);

static_assert(sizeof(b8)  == 1);

static_assert(sizeof(c8)  == 1);

// ================================================================================================