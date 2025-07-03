#pragma once

#define VYASSERT_MSG(condition, message)  \
	{                                     \
		if (!condition)                   \
		{                                 \
			assert(condition && message); \
		}                                 \
	}

#define VYASSERT(condition)               \
	{                                     \
		if (!condition)                   \
		{                                 \
			assert(condition);            \
		}                                 \
	}