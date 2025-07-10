#pragma once



#define VY_DEBUG_MODE


#define VY_LOG_ENABLED 1
#define VY_LIBRARY_IMPLEMENTATION 1


// Taken from https://github.com/NazaraEngine/NazaraUtils/blob/main/include/NazaraUtils/Prerequisites.hpp#L94

#if defined(__x86_64__) || defined(_M_X64)    || \
defined(__aarch64__)    || defined(__ppc64__) || \
defined(__mips64)       || defined(__ia64__)  || \
defined(__powerpc64__)  || defined(__64BIT__) || \
defined(_WIN64)
	#define VY_64BIT_SYSTEM 1
#else
	/* Then handle the sizeof check in the compiled code, not preprocessor */
	#if (sizeof(void*) == 8)
		#define VY_64BIT_SYSTEM 1
	#else
		#define VY_64BIT_SYSTEM 0
	#endif
#endif



/* ==================== COMPILER ==================== */

// MARK: MSVC
#if defined(_MSC_VER)

	#define VY_COMPILER_MSVC
	#define VY_COMPILER_MSVC_VER                   _MSC_VER
	#define VY_DEPRECATED(txt)                     __declspec(deprecated(txt))
	#define VY_PRETTY_FUNCTION                     __FUNCSIG__

	#define VY_CHECK_MSVC_VER(ver)                 (VY_COMPILER_MSVC_VER >= ver)
    #define VYINLINE                               inline
	#define VYNODISCARD                            [[nodiscard]]
	#define VY_PRAGMA(x)                           __pragma(x)

	#define VY_WARNING_MSVC_DISABLE(...)           VY_PRAGMA(warning(disable: __VA_ARGS__))
	#define VY_WARNING_POP()                       VY_PRAGMA(warning(pop))
	#define VY_WARNING_PUSH()                      VY_PRAGMA(warning(push))

	// __cplusplus isn't respected on MSVC without /Zc:__cplusplus flag
	#define VY_CPP_VER                             _MSVC_LANG

// MARK: CLANG
#elif defined(__clang__)

	#define VY_COMPILER_CLANG
	#define VY_COMPILER_CLANG_VER                  (__clang_major__ * 100 + __clang_minor__)
	#define VY_DEPRECATED(txt)                     __attribute__((__deprecated__(txt)))
	#define VY_PRETTY_FUNCTION                     __PRETTY_FUNCTION__

	#define VY_CHECK_CLANG_VER(ver)                (VY_COMPILER_CLANG_VER >= ver)
	
	#define VY_PRAGMA(x)                           _Pragma(#x)

	#define VY_WARNING_CLANG_DISABLE(warn)         VY_PRAGMA(clang diagnostic ignored warn)
	#define VY_WARNING_CLANG_GCC_DISABLE(warn)     VY_PRAGMA(clang diagnostic ignored warn)
	#define VY_WARNING_POP()                       VY_PRAGMA(clang diagnostic pop)
	#define VY_WARNING_PUSH()                      VY_PRAGMA(clang diagnostic push)

// MARK: GCC
#elif defined(__GNUC__) || defined(__MINGW32__)

	#define VY_COMPILER_GCC
	#define VY_COMPILER_GCC_VER                    (__GNUC__ * 100 + __GNUC_MINOR__)
	#define VY_DEPRECATED(txt)                     __attribute__((__deprecated__(txt)))
	#define VY_PRETTY_FUNCTION                     __PRETTY_FUNCTION__

	#define VY_CHECK_GCC_VER(ver)                  (VY_COMPILER_GCC_VER >= ver)

	#define VY_PRAGMA(x)                           _Pragma(#x)

	#define VY_WARNING_CLANG_GCC_DISABLE(warn)     VY_PRAGMA(GCC diagnostic ignored warn)
	#define VY_WARNING_GCC_DISABLE(warn)           VY_PRAGMA(GCC diagnostic ignored warn)
	#define VY_WARNING_POP()                       VY_PRAGMA(GCC diagnostic pop)
	#define VY_WARNING_PUSH()                      VY_PRAGMA(GCC diagnostic push)

// MARK: ICC
#elif defined(__INTEL_COMPILER) || defined(__ICL)

	#define VY_COMPILER_ICC
	#define VY_COMPILER_ICC_VER                    __INTEL_COMPILER
	#define VY_DEPRECATED(txt)                     [[deprecated(txt)]]
	#define VY_PRETTY_FUNCTION                     __FUNCTION__
	
	#define VY_CHECK_ICC_VER(ver)                  (VY_COMPILER_ICC_VER >= ver)

	#define VY_PRAGMA(x)                           _Pragma(x)

	#define VY_WARNING_ICC_DISABLE(...)            VY_PRAGMA(warning(disable: __VA_ARGS__))
	#define VY_WARNING_POP()                       VY_PRAGMA(warning(pop))
	#define VY_WARNING_PUSH()                      VY_PRAGMA(warning(push))

#else
    #error "Potentially Unsuported Compiler"
	#define VY_COMPILER_UNKNOWN

	#pragma message This compiler is not fully supported
#endif

#ifndef VY_CHECK_CLANG_VER
#define VY_CHECK_CLANG_VER(ver) 0
#endif

#ifndef VY_CHECK_ICC_VER
#define VY_CHECK_ICC_VER(ver) 0
#endif

#ifndef VY_CHECK_GCC_VER
#define VY_CHECK_GCC_VER(ver) 0
#endif

#ifndef VY_CHECK_MSVC_VER
#define VY_CHECK_MSVC_VER(ver) 0
#endif

#ifndef VY_CPP_VER
#define VY_CPP_VER __cplusplus
#endif

#ifndef VY_DEPRECATED
#define VY_DEPRECATED(txt) [[deprecated(txt)]]
#endif

#ifndef VY_PRAGMA
#define VY_PRAGMA(x) _Pragma(#x)
#endif

#ifndef VY_PRETTY_FUNCTION
#define VY_PRETTY_FUNCTION __func__
#endif

#ifndef VY_WARNING_CLANG_DISABLE
#define VY_WARNING_CLANG_DISABLE(warn)
#endif

#ifndef VY_WARNING_CLANG_GCC_DISABLE
#define VY_WARNING_CLANG_GCC_DISABLE(warn)
#endif

#ifndef VY_WARNING_GCC_DISABLE
#define VY_WARNING_GCC_DISABLE(warn)
#endif

#ifndef VY_WARNING_ICC_DISABLE
#define VY_WARNING_ICC_DISABLE(warn)
#endif

#ifndef VY_WARNING_MSVC_DISABLE
#define VY_WARNING_MSVC_DISABLE(...)
#endif

#ifndef VY_WARNING_POP
#define VY_WARNING_POP()
#endif

#ifndef VY_WARNING_PUSH
#define VY_WARNING_PUSH()
#endif


// MARK: C++ version
#define VY_CPP98 199711L
#define VY_CPP11 201103L
#define VY_CPP14 201402L
#define VY_CPP17 201703L
#define VY_CPP20 202002L
#define VY_CPP23 202302L

#define VY_CHECK_CPP_VER(ver) (VY_CPP_VER >= ver)

#if !VY_CHECK_CPP_VER(VY_CPP17)
	#error VyLib requires C++17 or higher
#endif

// MARK: WIN32
#if defined(_WIN32)
	#define VY_PLATFORM_DESKTOP
	#define VY_PLATFORM_WINDOWS

	#define VY_EXPORT __declspec(dllexport)
	#define VY_IMPORT __declspec(dllimport)

	// Somes defines for windows.h include..
	#if defined(VY_BUILD)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN
		#endif

		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
	#endif

// MARK: LINUX
#elif defined(__linux__)
	#define VY_PLATFORM_DESKTOP
	#define VY_PLATFORM_LINUX
	#define VY_PLATFORM_POSIX

	#define VY_EXPORT __attribute__((visibility("default")))
	#define VY_IMPORT __attribute__((visibility("default")))

// MARK: APPLE
#elif defined(__APPLE__)
	#define VY_PLATFORM_DESKTOP
	#define VY_PLATFORM_MACOS
	#define VY_PLATFORM_BSD
	#define VY_PLATFORM_POSIX

	#define VY_EXPORT __attribute__((visibility("default")))
	#define VY_IMPORT __attribute__((visibility("default")))

// MARK: EMSCRIPTEN
#elif defined(__EMSCRIPTEN__)
	#define VY_PLATFORM_WEB
	#define VY_PLATFORM_POSIX

	#define VY_EXPORT __attribute__((visibility("default")))
	#define VY_IMPORT __attribute__((visibility("default")))

#else
	#pragma message "This operating system is not fully supported by the VyLib Library"

	#define VY_PLATFORM_UNKNOWN
	#define VY_EXPORT
	#define VY_IMPORT
#endif



// MARK: Feature checking
#ifdef __has_cpp_attribute
	#define VY_HAS_CPP_ATTRIBUTE(attr) __has_cpp_attribute(attr)
#else
	#define VY_HAS_CPP_ATTRIBUTE(attr) (0)
#endif

// MARK: "Assume" attribute
#ifndef VY_NO_ASSUME_ATTRIBUTE

	#if VY_CHECK_CPP_VER(VY_CPP23) || VY_HAS_CPP_ATTRIBUTE(assume)
		#define VY_ASSUME(expr) [[assume(expr)]]
	#endif

	#ifndef VY_ASSUME
		#if defined(VY_COMPILER_CLANG)
			#define VY_ASSUME(expr) __builtin_assume(expr)
		#endif

		#if defined(VY_COMPILER_GCC)

			// __attribute__(assume) is supported starting with GCC 13
			#if __GNUC__ >= 13
				#define VY_ASSUME(expr) __attribute__(assume(expr))
			#endif

		#endif

		#if defined(VY_COMPILER_MSVC)
			#define VY_ASSUME(expr) __assume(expr)
		#endif

	#endif

#endif // VY_NO_ASSUME_ATTRIBUTE







// MARK: FORCE INLINE
#ifndef VY_NO_FORCEINLINE_ATTRIBUTE

#ifndef VY_FINLINE

	#if defined(VY_COMPILER_CLANG) || defined(VY_COMPILER_GCC)
		#define VY_FINLINE __attribute__((always_inline)) inline
	#endif

	#if defined(VY_COMPILER_MSVC)
		#define VY_FINLINE __forceinline
	#endif

#endif

#endif // VY_NO_FORCEINLINE_ATTRIBUTE

// MARK: LIKELY / UNLIKELY
#ifndef VY_NO_LIKELY_ATTRIBUTE

	#if VY_CHECK_CPP_VER(VY_CPP20) || VY_HAS_CPP_ATTRIBUTE(likely)
		#define VY_LIKELY(expr) (expr) [[likely]]
	#endif

	#if VY_CHECK_CPP_VER(VY_CPP20) || VY_HAS_CPP_ATTRIBUTE(unlikely)
		#define VY_UNLIKELY(expr) (expr) [[unlikely]]
	#endif

	#if defined(VY_COMPILER_CLANG) || defined(VY_COMPILER_GCC) || defined(VY_COMPILER_ICC)

		#ifndef VY_LIKELY
			#define VY_LIKELY(expr) (__builtin_expect(!!(expr), 1))
		#endif

		#ifndef VY_UNLIKELY
			#define VY_UNLIKELY(expr) (__builtin_expect(!!(expr), 0))
		#endif

	#endif

#endif // VY_NO_LIKELY_ATTRIBUTE


// MARK: Unreachable macro
#ifndef VY_NO_UNREACHABLE_MACRO

	#if defined(VY_COMPILER_CLANG) || defined(VY_COMPILER_GCC) || defined(VY_COMPILER_ICC)
		#define VY_UNREACHABLE() __builtin_unreachable()
	#elif defined(VY_COMPILER_MSVC)
		#define VY_UNREACHABLE() __assume(false)
	#endif

#endif // VY_NO_UNREACHABLE_MACRO



// MARK: Fallbacks
#ifndef VY_ASSUME
	#define VY_ASSUME(expr)
#endif

#ifndef VY_FINLINE
	#define VY_FINLINE inline
#endif

#ifndef VY_LIKELY
	#define VY_LIKELY(expr) (expr)
#endif

#ifndef VY_UNLIKELY
	#define VY_UNLIKELY(expr) (expr)
#endif

#ifndef VY_UNREACHABLE
	#define VY_UNREACHABLE() throw Nz::UnreachableError{};
#endif


#define VY_NOOP(...) do { (void)0; } while (0)
#define VY_UNUSED(x) do { (void)(x); } while (0)
#define VY_UNUSED_2(a, b) VY_UNUSED(a); VY_UNUSED(b)
#define VY_UNUSED_3(a, b, c) VY_UNUSED_2(a, b); VY_UNUSED(c)
#define VY_UNUSED_4(a, b, c, d) VY_UNUSED_3(a, b, c); VY_UNUSED(d)
#define VY_UNUSED_5(a, b, c, d, e) VY_UNUSED_4(a, b, c, d); VY_UNUSED(e)
#define VY_UNUSED_6(a, b, c, d, e, f) VY_UNUSED_5(a, b, c, d, e); VY_UNUSED(f)
#define VY_UNUSED_7(a, b, c, d, e, f, g) VY_UNUSED_6(a, b, c, d, e, f); VY_UNUSED(g)

#ifdef VY_COMPILER_MSVC
	#define VY_LIKELY(x) (x)
	#define VY_UNLIKELY(x) (x)
	#define VY_UNREACHABLE() __assume(0)
	#define VY_ALIGN_DECL(align_, decl) __declspec(align(align_)) decl
	#define VY_THREAD __declspec(thread)

#elif defined(VY_COMPILER_GCC) || defined(VY_COMPILER_CLANG)
	#define VY_LIKELY(x)               __builtin_expect((x), 1)
	#define VY_UNLIKELY(x)             __builtin_expect((x), 0)
	#define VY_UNREACHABLE()           __builtin_unreachable()
	#define VY_ALIGN_DECL(align, decl) decl __attribute__ ((aligned(align)))
	#define VY_THREAD                  __thread

#else
	Unknown compiler
#endif

















// #if defined (VY_COMPILER_MSVC)

//     #define VYINLINE                                inline
//     #define VY_FINLINE                              __forceinline
//     #define VY_DEBUG_BREAK                          __debugbreak();
//     #define VY_DISABLE_WARNING(...)                 __pragma(warning(disable : __VA_ARGS__))

// #elif defined(VY_COMPILER_CLANG)



// #elif defined(VY_COMPILER_GCC)

// 	#define VY_PRAGMA(x) _Pragma(#x)

// 	#define VY_WARNING_CLANG_GCC_DISABLE(warn) VY_PRAGMA(GCC diagnostic ignored warn)
// 	#define VY_WARNING_GCC_DISABLE(warn) VY_PRAGMA(GCC diagnostic ignored warn)
// 	#define VY_WARNING_POP() VY_PRAGMA(GCC diagnostic pop)
// 	#define VY_WARNING_PUSH() VY_PRAGMA(GCC diagnostic push)

// #else

//     #define VYINLINE                                inline
//     #define VY_FINLINE                              always_inline
//     #define VY_DEBUG_BREAK                          raise(SIGTRAP);


// #endif
