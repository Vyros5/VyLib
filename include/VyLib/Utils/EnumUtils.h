#pragma once

#include <type_traits>
#include <magic_enum.hpp>

#include "VyLib/Types/StringTypes.h"


/**
 *  enum class TestFlags 
 *  { 
 *      None = 0, 
 *      A    = 1 << 0, 
 *      B    = 1 << 1, 
 *  };
 * 
 *  template <> struct has_flags<TestFlags> : std::true_type {};
 * 
 *  Common Operations:
 * 
 *      TestFlags flags{TestFlags::A};
 * 
 *      flags |=  TestFlags::B;                  // Add a flag.
 *      flags |=  (TestFlags::A | TestFlags::B); // Add multiple flags.
 *      flags &= ~TestFlags::A;                  // Remove a flag.
 *      flags &= ~(TestFlags::A | TestFlags::B); // Remove multiple flags.
 * 
 *      bool(flags & TestFlags::A);              // Check if a flag is set.
 *      flags == (TestFlags::A | TestFlags::B);  // Check the exact set of flags.
 */


template <typename T> 
struct has_flags : std::false_type {};

template <typename T> 
constexpr auto has_flags_v = has_flags<T>::value;


template <typename T>
concept ScopedEnumWithFlags = std::is_scoped_enum_v<T> && has_flags_v<T>;

template <ScopedEnumWithFlags T> 
[[nodiscard]] constexpr auto operator~(T a) 
{
    return static_cast<T>(~static_cast<std::underlying_type_t<T>>(a));
}

template <ScopedEnumWithFlags T>
[[nodiscard]] constexpr auto operator|(T lhs, T rhs) 
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) | static_cast<std::underlying_type_t<T>>(rhs));
}

template <ScopedEnumWithFlags T> inline T& operator|=(T& lhs, T rhs) 
{
    return lhs = lhs | rhs;
}

template <ScopedEnumWithFlags T>
[[nodiscard]] constexpr auto operator&(T lhs, T rhs) 
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) & static_cast<std::underlying_type_t<T>>(rhs));
}

template <ScopedEnumWithFlags T> 
inline T& operator&=(T& lhs, T rhs) 
{
    return lhs = lhs & rhs;
}





template <typename EnumType>
struct IsEnumFlags
{
    static const bool value = false;
};

#define VY_DECLARE_FLAGS(T, UT)                                                                        \
    inline T  operator| (T a, T b) { return static_cast<T>(static_cast<UT>(a) | static_cast<UT>(b)); } \
    inline UT operator& (T a, T b) { return (static_cast<UT>(a) & static_cast<UT>(b)); }               \
    inline T& operator&=(T& a, T b) {                                                                  \
        a = static_cast<T>(a & b);                                                                     \
        return a;                                                                                      \
    }                                                                                                  \
    inline T& operator|=(T& a, T b) {                                                                  \
        a = a | b;                                                                                     \
        return a;                                                                                      \
    }                                                                                                  \
    inline T operator~(T a) { return static_cast<T>(~static_cast<UT>(a)); }                            \
    inline bool operator==(T& a, UT b) { return static_cast<UT>(a) == b; }                             \
    inline bool operator!=(T& a, UT b) { return !(a == b); }


// template <>                          \
// struct IsEnumFlags<EnumType>         \
// {                                    \
//     static const bool value = true;  \
// };


template <typename EnumType>
typename std::enable_if<IsEnumFlags<EnumType>::value, EnumType>::type operator|(EnumType lhs, EnumType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
}

template <typename EnumType>
typename std::enable_if<IsEnumFlags<EnumType>::value, EnumType>::type operator&(EnumType lhs, EnumType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));
}

template <typename EnumType>
typename std::enable_if<IsEnumFlags<EnumType>::value, EnumType>::type operator^(EnumType lhs, EnumType rhs) 
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) ^ static_cast<UnderlyingType>(rhs));
}

template <typename EnumType>
typename std::enable_if<IsEnumFlags<EnumType>::value, EnumType>::type& operator|=(EnumType& lhs, EnumType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    lhs = static_cast<EnumType>(static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
    return lhs;
}

template <typename EnumType>
typename std::enable_if<IsEnumFlags<EnumType>::value, EnumType>::type& operator&=(EnumType& lhs, EnumType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    lhs = static_cast<EnumType>(static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));
    return lhs;
}

template <typename EnumType>
typename std::enable_if<IsEnumFlags<EnumType>::value, EnumType>::type& operator^=(EnumType& lhs, EnumType rhs) 
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    lhs = static_cast<EnumType>(static_cast<UnderlyingType>(lhs) ^ static_cast<UnderlyingType>(rhs));
    return lhs;
}

template <typename EnumType>
typename std::enable_if<IsEnumFlags<EnumType>::value, EnumType>::type operator~(EnumType rhs) 
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    return static_cast<EnumType>(~static_cast<UnderlyingType>(rhs));
}

template <typename EnumType>
typename std::enable_if<IsEnumFlags<EnumType>::value, bool>::type HasFlags(EnumType lhs, EnumType rhs) 
{
    return (lhs & rhs) == rhs;
}


namespace Vy::EnumUtils
{
	template<typename Enum>
	cstring GetEnumName(Enum value)
	{
		return magic_enum::enum_name(value).data();
	}

	template<typename Enum>
	Enum GetEnumFromName(const String& name)
	{
		auto value = magic_enum::enum_cast<Enum>(name);
		if (value.has_value()) 
        {
			return value.value();
		}

		// EG_EDITOR_WARN("Couldn't get enum from name: {}", name);
		return Enum();
	}
}