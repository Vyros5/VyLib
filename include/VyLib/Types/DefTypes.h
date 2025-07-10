#pragma once

#include "VyLib/Platform.h"

#if !defined(alignof)
	#define alignof(x) __alignof(x)
#endif

#if !defined(__va_copy)
	#define __va_copy(dest, src) (dest = src)
#endif

#define countof(arr) (sizeof(arr)/sizeof(arr[0]))

#define container_of(ptr, type, member) ((char*)ptr - offsetof(type, member))

#define VY_STRINGIZE(value) #value


#define VY_NOOP(...) do { (void)0; } while (0)
#define VY_UNUSED(x) do { (void)(x); } while (0)
#define VY_UNUSED_2(a, b) VY_UNUSED(a); VY_UNUSED(b)
#define VY_UNUSED_3(a, b, c) VY_UNUSED_2(a, b); VY_UNUSED(c)
#define VY_UNUSED_4(a, b, c, d) VY_UNUSED_3(a, b, c); VY_UNUSED(d)
#define VY_UNUSED_5(a, b, c, d, e) VY_UNUSED_4(a, b, c, d); VY_UNUSED(e)
#define VY_UNUSED_6(a, b, c, d, e, f) VY_UNUSED_5(a, b, c, d, e); VY_UNUSED(f)
#define VY_UNUSED_7(a, b, c, d, e, f, g) VY_UNUSED_6(a, b, c, d, e, f); VY_UNUSED(g)

#define VY_BIT(x) (1 << x)