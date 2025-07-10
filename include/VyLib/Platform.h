#pragma once


/**
 * Pre-defined C/C++ Compiler Macros:
 *      https://github.com/cpredef/predef
 */

/* ============================================================================================= */
// MARK: COMPILER

#define VY_COMPILER_MSVC  0
#define VY_COMPILER_CLANG 0
#define VY_COMPILER_GCC   0
#define VY_COMPILER_ICC   0

#if defined(_MSC_VER)
#   undef VY_COMPILER_MSVC
#   define VY_COMPILER_MSVC 1



#elif defined(__clang__)
#   undef VY_COMPILER_CLANG
#   define VY_COMPILER_CLANG 1

#   define VY_COMPILER_NAME "Clang"
#   define VY_COMPILER_CLANG_VER                  (__clang_major__ * 100 + __clang_minor__)
#   define VY_CHECK_CLANG_VER(ver)                (VY_COMPILER_CLANG_VER >= ver)
    
#elif defined(__GNUC__)
#   undef VY_COMPILER_GCC
#   define VY_COMPILER_GCC 1

#   define VY_COMPILER_NAME "GCC"
#   define VY_COMPILER_GCC_VER                    (__GNUC__ * 100 + __GNUC_MINOR__)
#   define VY_CHECK_GCC_VER(ver)                  (VY_COMPILER_GCC_VER >= ver)

#elif defined(__INTEL_COMPILER) || defined(__ICL)
#   undef VY_COMPILER_ICC
#   define VY_COMPILER_ICC 1

#   define VY_COMPILER_NAME "ICC"
#   define VY_COMPILER_ICC_VER                    __INTEL_COMPILER
#   define VY_CHECK_ICC_VER(ver)                  (VY_COMPILER_ICC_VER >= ver)

#else
#   error "VY_COMPILER_* is not defined!"
#endif


/* ============================================================================================= */
// MARK: PLATFORM

#define VY_PLATFORM_WINDOWS    0
#define VY_PLATFORM_ANDROID    0
#define VY_PLATFORM_LINUX      0
#define VY_PLATFORM_IOS        0
#define VY_PLATFORM_OSX        0
#define VY_PLATFORM_EMSCRIPTEN 0

#if defined(_WIN32) || defined(_WIN64)
#   undef  VY_PLATFORM_WINDOWS
#   define VY_PLATFORM_WINDOWS 1
#   define VY_PLATFORM_NAME "windows"

#elif defined(__ANDROID__) // Android compiler defines __linux__
#   undef  VY_PLATFORM_ANDROID
#   define VY_PLATFORM_ANDROID 1
#   define VY_PLATFORM_NAME "android"

#elif defined(__linux__)
#   undef  VY_PLATFORM_LINUX
#   define VY_PLATFORM_LINUX 1
#   define VY_PLATFORM_NAME "linux"

#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#   undef  VY_PLATFORM_IOS
#   define VY_PLATFORM_IOS 1
#   define VY_PLATFORM_NAME "ios"

#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#   undef  VY_PLATFORM_OSX
#   define VY_PLATFORM_OSX 1
#   define VY_PLATFORM_NAME "osx"

#elif defined(__EMSCRIPTEN__)
#   undef  VY_PLATFORM_EMSCRIPTEN
#   define VY_PLATFORM_EMSCRIPTEN 1
#   define VY_PLATFORM_NAME "html5"
#else
#   error "VY_PLATFORM_* is not defined!"
#endif


/* ============================================================================================= */
// MARK: CPU

#define VY_MACHINE_X86   0
#define VY_MACHINE_X64   0
#define VY_MACHINE_AMD64 0
#define VY_MACHINE_ARM   0
#define VY_MACHINE_ARM64 0



#if defined(_M_IX86) || defined(__i386__)
#   undef  VY_MACHINE_X86
#   define VY_MACHINE_X86  1
#   define VY_MACHINE_NAME "x86"

#elif defined(_M_X64) || defined(__x86_64__)
#   undef  VY_MACHINE_X64
#   define VY_MACHINE_X64  1
#   define VY_MACHINE_NAME "x64"

#elif defined(_M_AMD64) || defined(__amd64__)
#   undef  VY_MACHINE_AMD64
#   define VY_MACHINE_AMD64 1
#   define VY_MACHINE_NAME  "AMD64"

#elif defined(_M_ARM) || defined(__arm__)
#   undef  VY_MACHINE_ARM
#   define VY_MACHINE_ARM 1
#   define VY_MACHINE_NAME "ARM"

#elif defined(_M_ARM64) || defined(__aarch64__)
#   undef  VY_MACHINE_ARM64
#   define VY_MACHINE_ARM64 1
#   define VY_MACHINE_NAME  "ARM64"

#else
#   error "VY_MACHINE_* is not defined!"
#endif 


/* ============================================================================================= */
// MARK: ARCH.

#define VY_ARCH_32BIT 0
#define VY_ARCH_64BIT 0

#if defined(__x86_64__)     || defined(_M_X64)    || \
    defined(__aarch64__)    || defined(__ppc64__) || \
    defined(__mips64)       || defined(__ia64__)  || \
    defined(__powerpc64__)  || defined(__64BIT__) || \
    defined(_WIN64)

	#undef  VY_ARCH_64BIT
	#define VY_ARCH_64BIT 64
    #define VY_ARCH_NAME  "64-bit"
#else
	#undef  VY_ARCH_32BIT
	#define VY_ARCH_32BIT 32
    #define VY_ARCH_NAME  "32-bit"
#endif


/* ============================================================================================= */
// MARK: Compiler Specific


#if VY_COMPILER_MSVC

#   define VY_LIKELY(x)                           (x)
#   define VY_UNLIKELY(x)                         (x)
#   define VY_UNREACHABLE()                       __assume(0)
#   define VY_ALIGN_DECL(align_, decl)            __declspec(align(align_)) decl
#   define VY_THREAD                              __declspec(thread)

#   define VYINLINE                               inline
#   define VY_FINLINE                             __forceinline
#   define VYNODISCARD                            [[nodiscard]]
#   define VY_DEBUG_BREAK()                       __debugbreak()
#   define VY_DEPRECATED(txt)                     __declspec(deprecated(txt))
#   define VY_PRETTY_FUNCTION                     __FUNCSIG__

#   define VY_PRAGMA(x)                           __pragma(x)

#   define VY_WARNING_MSVC_DISABLE(...)           VY_PRAGMA(warning(disable: __VA_ARGS__))
#   define VY_WARNING_POP()                       VY_PRAGMA(warning(pop))
#   define VY_WARNING_PUSH()                      VY_PRAGMA(warning(push))

#elif VY_COMPILER_GCC || VY_COMPILER_CLANG

#   define VY_LIKELY(x)                           __builtin_expect((x), 1)
#   define VY_UNLIKELY(x)                         __builtin_expect((x), 0)
#   define VY_UNREACHABLE()                       __builtin_unreachable()
#   define VY_ALIGN_DECL(align, decl)             decl __attribute__ ((aligned(align)))
#   define VY_THREAD                              __thread
#   define VYINLINE                               x
#   define VY_FINLINE                             __attribute__((always_inline)) inline
#   define VYNODISCARD                            [[nodiscard]]
#   define VY_DEBUG_BREAK()                       __builtin_trap()
#   define VY_DEPRECATED(txt)                     __attribute__((__deprecated__(txt)))
#   define VY_PRETTY_FUNCTION                     __PRETTY_FUNCTION__
    
#   define VY_PRAGMA(x)                           _Pragma(#x)

#   define VY_WARNING_CLANG_DISABLE(warn)         VY_PRAGMA(clang diagnostic ignored warn)
#   define VY_WARNING_CLANG_GCC_DISABLE(warn)     VY_PRAGMA(clang diagnostic ignored warn)
#   define VY_WARNING_POP()                       VY_PRAGMA(clang diagnostic pop)
#   define VY_WARNING_PUSH()                      VY_PRAGMA(clang diagnostic push)

#elif VY_COMPILER_ICC

#   define VYINLINE                               inline
#   define VY_FINLINE                             __attribute__((always_inline)) inline
#   define VYNODISCARD                            [[nodiscard]]
#   define VY_DEBUG_BREAK()                       raise(SIGTRAP)
#   define VY_DEPRECATED(txt)                     [[deprecated(txt)]]
#   define VY_PRETTY_FUNCTION                     __FUNCTION__

#   define VY_PRAGMA(x)                           _Pragma(x)

#   define VY_WARNING_ICC_DISABLE(...)            VY_PRAGMA(warning(disable: __VA_ARGS__))
#   define VY_WARNING_POP()                       VY_PRAGMA(warning(pop))
#   define VY_WARNING_PUSH()                      VY_PRAGMA(warning(push))

#else
#   error "Unknown compiler"
#endif



/* ============================================================================================= */
// MARK: Fallbacks

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