#pragma once



/* ==================== COMPILER ==================== */
#if defined(_MSC_VER)

    #define VY_COMPILER_MSVC

#elif defined(__clang__)

    #define VY_COMPILER_CLANG

#elif defined(__GNUC__)

    #define VY_COMPILER_GCC

#else
    #error "Potentially Unsuported Compiler"
#endif



#if defined (VY_COMPILER_MSVC)

    #define VYINLINE                                inline
    #define VY_FORCE_INLINE                         __forceinline
    #define VY_DEBUG_BREAK                          __debugbreak();
    #define VY_WARNING_PUSH()                       __pragma(warning(push))
    #define VY_WARNING_POP()                        __pragma(warning(pop))
    #define VY_DISABLE_WARNING(warning_number)      __pragma( warning( disable : warning_number ) )
    #define VY_CONCAT_OPERATOR(x, y)                x##y

#else

    #define VYINLINE                                inline
    #define VY_FORCE_INLINE                         always_inline
    #define VY_DEBUG_BREAK                          raise(SIGTRAP);
    #define VY_WARNING_PUSH()                       
    #define VY_WARNING_POP()                        
    #define VY_CONCAT_OPERATOR(x, y)                x y

#endif

#define VY_STRINGIZE( L )                           #L 
#define VY_MAKESTRING( L )                          VY_STRINGIZE( L )
#define VY_CONCAT(x, y)                             VY_CONCAT_OPERATOR(x, y)
#define VY_LINE_STRING                              VY_MAKESTRING( __LINE__ ) 
#define VY_FILELINE(MESSAGE)                        __FILE__ "(" VY_LINE_STRING ") : " MESSAGE

// Unique names
#define VY_UNIQUE_SUFFIX(PARAM)                     VY_CONCAT(PARAM, __LINE__ )

/* NODISCARD - Compiler Hint - Useful for functions that modify the obj/params but also returns something. (func cannot be const) */
#define VYNODISCARD                                 [[nodiscard]]

