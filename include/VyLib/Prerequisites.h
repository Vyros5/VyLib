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

	#ifdef __MINGW32__
		#define VY_COMPILER_MINGW
		#ifdef __MINGW64_VERSION_MAJOR
			#define VY_COMPILER_MINGW_W64
		#endif
	#endif

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

	#ifdef __MINGW32__
		#define VY_COMPILER_MINGW
		#ifdef __MINGW64_VERSION_MAJOR
			#define VY_COMPILER_MINGW_W64
		#endif
	#endif

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



// Detect MinGW thread model
#ifdef VY_COMPILER_MINGW
	#if defined(__USING_MCFGTHREAD__)
		#define VY_COMPILER_MINGW_THREADS_MCF
	#elif defined(_REENTRANT)
		#define VY_COMPILER_MINGW_THREADS_POSIX
	#else
		#define VY_COMPILER_MINGW_THREADS_WIN32
	#endif
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


// C++ version
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

// Try to identify target platform via defines
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

		#if VYLIBUTILS_WINDOWS_NT6
			#define VY_WINNT 0x0600
		#else
			#define VY_WINNT 0x0501
		#endif

		// Keep the actual define if existing and greater than our requirement
		#if defined(_WIN32_WINNT)
			#if _WIN32_WINNT < VY_WINNT
				#undef _WIN32_WINNT
				#define _WIN32_WINNT VY_WINNT
			#endif
		#else
			#define _WIN32_WINNT VY_WINNT
		#endif
	#endif

#elif defined(__ANDROID__)
	// android/ndk-version.h was added with NDK 16 so we should be safe, but an error is better than nothing
	#if !__has_include(<android/ndk-version.h>)
		#error VyLib requires a more recent Android NDK version, please update
	#endif
	#include <android/ndk-version.h>
	#define VY_PLATFORM_MOBILE
	#define VY_PLATFORM_ANDROID
	#define VY_PLATFORM_POSIX

	#define VY_PLATFORM_ANDROID_NDK_VER __NDK_MAJOR__
	#define VY_CHECK_NDK_VER(ver) (VY_PLATFORM_ANDROID_NDK_VER >= ver)

	#define VY_EXPORT __attribute__((visibility("default")))
	#define VY_IMPORT __attribute__((visibility("default")))

#elif defined(__linux__)
	#define VY_PLATFORM_DESKTOP
	#define VY_PLATFORM_LINUX
	#define VY_PLATFORM_POSIX

	#define VY_EXPORT __attribute__((visibility("default")))
	#define VY_IMPORT __attribute__((visibility("default")))

#elif defined(__FreeBSD__)
	#define VY_PLATFORM_BSD
	#define VY_PLATFORM_FREEBSD
	#define VY_PLATFORM_POSIX

	#define VY_EXPORT __attribute__((visibility("default")))
	#define VY_IMPORT __attribute__((visibility("default")))

#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE
		#define VY_PLATFORM_MOBILE
		#define VY_PLATFORM_IOS
	#else
		#define VY_PLATFORM_DESKTOP
		#define VY_PLATFORM_MACOS
	#endif
	#define VY_PLATFORM_BSD
	#define VY_PLATFORM_POSIX

	#define VY_EXPORT __attribute__((visibility("default")))
	#define VY_IMPORT __attribute__((visibility("default")))

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


#ifndef VY_CHECK_NDK_VER
	#define VY_CHECK_NDK_VER(ver) 0
#endif

// Feature checking
#ifdef __has_cpp_attribute
	#define VY_HAS_CPP_ATTRIBUTE(attr) __has_cpp_attribute(attr)
#else
	#define VY_HAS_CPP_ATTRIBUTE(attr) (0)
#endif

// "Assume" attribute
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







// "Force inline" attribute
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

// "Likely"/"unlikely" attributes
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

// Unreachable macro
#ifndef VY_NO_UNREACHABLE_MACRO

#if defined(VY_COMPILER_CLANG) || defined(VY_COMPILER_GCC) || defined(VY_COMPILER_ICC)
	#define VY_UNREACHABLE() __builtin_unreachable()
#elif defined(VY_COMPILER_MSVC)
	#define VY_UNREACHABLE() __assume(false)
#endif

#endif // VY_NO_UNREACHABLE_MACRO

// Fallbacks

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


// Detect arch
#ifndef VY_NO_ARCH_DETECTION

	#if defined(__arm__) || defined(__thumb__) || defined(__ARM_ARCH_7__) || defined(_M_ARM)
		#define VY_ARCH_arm
	#endif

	#if defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC) || defined(__arm64__)
		#define VY_ARCH_aarch64
	#endif

	#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64) || defined (_M_X64)
		#define VY_ARCH_x86_64
	#endif

	#if defined(__i386__) || defined(_M_IX86) || defined(_X86_)
		#define VY_ARCH_x86
	#endif

	#if defined(__wasm32__)
		#define VY_ARCH_wasm32
	#endif

	#if defined(__wasm64__)
		#define VY_ARCH_wasm64
	#endif

	#if defined(VY_ARCH_arm)     \
	  + defined(VY_ARCH_aarch64) \
	  + defined(VY_ARCH_x86_64)  \
	  + defined(VY_ARCH_x86)     \
	  + defined(VY_ARCH_wasm32)  \
	  + defined(VY_ARCH_wasm64)  \
    != 1

	#error No or multiple arch detected! Please open an issue with details about your target system. You can define VY_NO_ARCH_DETECTION to bypass this error.

	#endif

#endif // VY_NO_ARCH_DETECTION


// A bunch of useful macros
#define VyLibPrefix(a, prefix) prefix ## a
#define VyLibPrefixMacro(a, prefix) VyLibPrefix(a, prefix)
#define VyLibSuffix(a, suffix) a ## suffix
#define VyLibSuffixMacro(a, suffix) VyLibSuffix(a, suffix)
#define VyLibStringify(s) #s
#define VyLibStringifyMacro(s) VyLibStringify(s) // http://gcc.gnu.org/onlinedocs/cpp/Stringification.html#Stringification
#define VyLibUnused(a) (void) a

















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
