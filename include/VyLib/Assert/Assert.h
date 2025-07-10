#pragma once

#include <cassert>
#include <filesystem>

#include "VyLib/Log/Log.h"
#include "VyLib/Platform.h"

// Internal assertion implementation
#define VYASSERT_IMPL(condition, msg, ...) \
    do {                                   \
        if (!(condition))                  \
		{                                  \
            VYERROR(msg, __VA_ARGS__);     \
            VY_DEBUG_BREAK();              \
        }                                  \
    } while (0)


// Assertion with custom message
#define VYASSERT_MSG(condition, ...)                                   \
	{                                                                  \
		VYASSERT_IMPL(condition, "Assertion failed: {}", __VA_ARGS__); \
	}

// Assertion with default message
#define VYASSERT_NO_MSG(condition)                                                                                                         \
{                                                                                                                                          \
	VYASSERT_IMPL(condition, "Assertion `{}` failed at {}:{}", #condition, std::filesystem::path(__FILE__).filename().string(), __LINE__); \
}

// Macro chooser (1 arg = no msg, 2+ = with msg)
#define VY_GET_ASSERT_MACRO(_1, _2, NAME, ...) NAME
#define VYASSERT_CHOOSER(...) VY_GET_ASSERT_MACRO(__VA_ARGS__, VYASSERT_MSG, VYASSERT_NO_MSG)


// Dispatcher
#define VYASSERT(...) VYASSERT_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

// #define VYASSERT(condition)            \
// 	{                                     \
// 		if (!condition)                   \
// 		{                                 \
// 			assert(condition);            \
// 		}                                 \
// 	}

#define VY_STATIC_ASSERT(condition, ...) static_assert(condition, "" # __VA_ARGS__)


