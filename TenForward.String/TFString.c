// String.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

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

		memcpy(data, str, length * sizeof(wchar_t));
		memcpy(string.data, &data, sizeof(wchar_t*));
	}
	else
	{
		memcpy(string.data, str, length * sizeof(wchar_t));
	}

	return string;
}

wchar_t* TF_StringData(const TF_String* str)
{
	if (str->length > TF_SMALL_STRING_SIZE)
	{
		wchar_t* ptr;
		memcpy(&ptr, str->data, sizeof(wchar_t*));
		return ptr;
	}
	else
	{
		return str->data;
	}
}

void TF_StringDestroy(TF_String* str)
{
	if (str->length > TF_SMALL_STRING_SIZE)
	{
		wchar_t* ptr;
		memcpy(&ptr, str->data, sizeof(wchar_t*));
		free(ptr);
	}
}

