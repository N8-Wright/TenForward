#pragma once
#include <stdint.h>

struct String
{
	size_t length;
	size_t capacity;
#if _WIN64
	wchar_t data[8];
#elif _WIN32
	wchar_t data[12];
#endif
};

static_assert(sizeof(struct String) == 32, "Sizeof string should be 32 bytes");