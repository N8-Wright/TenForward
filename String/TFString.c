// String.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include <stdlib.h>
#include <string.h>

TF_String TF_StringCreateEx(wchar_t* str, size_t length)
{
	TF_String string;
	string.length = length;
	string.capacity = length;

	if (length > TF_SMALL_STRING_SIZE)
	{
		wchar_t* data = malloc(length * sizeof(wchar_t));
		if (data == NULL)
		{
			exit(1);
		}

		memcpy(string.data, data, sizeof(wchar_t*));
	}
	else
	{
		memcpy(string.data, str, length);
	}

	return string;
}
