// String.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

static inline wchar_t* GetDataPtr(const TF_String *str)
{
	wchar_t* ptr;
	memcpy(&ptr, str->data, sizeof(wchar_t*));
	return ptr;
}

TF_String TF_StringCreateEx(wchar_t* str, size_t length)
{
	TF_String string;
	string.length = length;

	if (length > TF_SMALL_STRING_SIZE)
	{
		string.capacity = length;
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
		string.capacity = TF_SMALL_STRING_SIZE;
		memcpy(string.data, str, length * sizeof(wchar_t));
	}

	return string;
}

const wchar_t* TF_StringData(const TF_String* str)
{
	if (str->capacity > TF_SMALL_STRING_SIZE)
	{
		return GetDataPtr(str);
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
		free(GetDataPtr(str));
	}
}

void TF_StringAppend(TF_String* str, const TF_String* other)
{
	size_t capacity = str->length + other->length;
	if (capacity > TF_SMALL_STRING_SIZE)
	{
		TF_StringResize(str, capacity);
		wchar_t* data = GetDataPtr(str);
		
		memcpy(&data[str->length], TF_StringData(other), other->length * sizeof(wchar_t));
	}
	else
	{
		memcpy(&str->data[str->length], TF_StringData(other), other->length * sizeof(wchar_t));
	}

	str->length = capacity;
}

void TF_StringResize(TF_String* str, size_t capacity)
{
	if (str->capacity <= TF_SMALL_STRING_SIZE)
	{
		if (capacity <= TF_SMALL_STRING_SIZE)
		{
			return;
		}
		else
		{
			wchar_t* data = malloc(capacity * sizeof(wchar_t));
			if (data == NULL)
			{
				exit(1);
			}

			memcpy(data, str->data, str->length * sizeof(wchar_t));
			memcpy(str->data, &data, sizeof(wchar_t*));
		}
		}
	else
	{
		wchar_t* data = GetDataPtr(str);
		if (capacity <= TF_SMALL_STRING_SIZE)
		{
			memcpy(str->data, data, capacity * sizeof(wchar_t));
			str->length = capacity;
			free(data);
		}
		else
		{
			void* result = realloc(data, capacity * sizeof(wchar_t));
			if (result == NULL)
			{
				exit(1);
			}

			data = result;
			memcpy(str->data, &data, sizeof(wchar_t*));
		}
	}

	str->capacity = capacity;
}
