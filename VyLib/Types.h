#pragma once

#include <cstdint>
#include <string>
#include <filesystem>

#include "VyLib/Defines.h"
#include <span>

// ----------------------------------------------
// Signed Types

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
// ----------------------------------------------
// Unsigned Types

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
// ----------------------------------------------
// Float Types

using f32 = float;
using f64 = double;
// ----------------------------------------------
// String Types

using cstring     = const char*;

using String      = std::string;
using StringView  = std::string_view;

using WString     = std::wstring;
using WStringView = std::wstring_view;

using StringList  = std::vector<String>;

// ----------------------------------------------

using Path = std::filesystem::path;

// ----------------------------------------------

using BinaryBuffer     = std::vector<u8>;
using BinaryBufferView = std::span<const u8>;

// ----------------------------------------------
static_assert(sizeof(bool)          == 1);
static_assert(sizeof(char)          == 1);
static_assert(sizeof(float)         == 4);
static_assert(sizeof(double)        == 8);
static_assert(sizeof(long long int) == 8);

static_assert(sizeof(i8)   == 1);
static_assert(sizeof(i16)  == 2);
static_assert(sizeof(i32)  == 4);
static_assert(sizeof(i64)  == 8);

static_assert(sizeof(u8)   == 1);
static_assert(sizeof(u16)  == 2);
static_assert(sizeof(u32)  == 4);
static_assert(sizeof(u64)  == 8);

static_assert(sizeof(f32)  == 4);
static_assert(sizeof(f64)  == 8);
// ----------------------------------------------

/**
 * @brief Enum values for success and failure. 
 *        To be used by functions as return values instead of booleans.
 */
enum VyResultEnum
{
    VY_FAILURE,
    VY_SUCCESS
};

/**
 * @brief Default enum for returning failure or success, instead of using a bool.
 */
struct VYNODISCARD VyResult
{
public:
    VyResult(VyResultEnum result) 
        : m_Enum(result) 
    {
    }

    void operator=(VyResultEnum  rhs)       { m_Enum = rhs; }
    bool operator==(VyResultEnum cmp) const { return m_Enum == cmp; }
    bool operator!=(VyResultEnum cmp) const { return m_Enum != cmp; }

    VYNODISCARD VY_FORCE_INLINE bool Succeeded() const { return m_Enum == VY_SUCCESS; }
    VYNODISCARD VY_FORCE_INLINE bool Failed()    const { return m_Enum == VY_FAILURE; }

    /**
     * @brief Used to silence compiler warnings, when success or failure doesn't matter.
     */
    VY_FORCE_INLINE void IgnoreResult()
    {
        /* dummy to be called when a return value is VYNODISCARD but the result is not needed */
    }

    /**
     * @brief Asserts that the function succeeded. In case of failure, the program will terminate.
     * If 'msg' is given, this will be the assert message. If 'details' is provided, msg should contain a formatting element ({}), e.g. "Error: {}".
     */
    void AssertSuccess(cstring szMsg = nullptr, cstring szDetails = nullptr) const;

private:
    VyResultEnum m_Enum;
};

/**
 * @brief Explicit conversion to VyResult, can be overloaded for arbitrary types.
 * This is intentionally not done via casting operator overload (or even additional constructors) 
 * since this usually comes with a considerable data loss.
 */
VYINLINE VyResult VyToResult(VyResult result)
{
    return result;
}




struct NonCopyable 
{
    VYINLINE constexpr NonCopyable() {}

    NonCopyable(const NonCopyable&)            = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};


struct NonMovable 
{
    VYINLINE constexpr NonMovable() {}

    NonMovable(NonMovable&&)            = delete;
    NonMovable& operator=(NonMovable&&) = delete;
};


