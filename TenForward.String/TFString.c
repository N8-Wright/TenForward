// String.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

_Check_return_ static inline wchar_t* GetDataPtr(_In_ const TF_String *str)
{
	wchar_t* ptr;
	memcpy(&ptr, str->data, sizeof(wchar_t*));
	return ptr;
}

TF_String TF_StringCreateEx(
	_In_reads_(length) const wchar_t* str,
	_In_ size_t length)
{
	TF_String string = { 0 };
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

TF_String TF_StringCreate(_In_ size_t capacity)
{
	TF_String string = { 0 };
	string.length = 0;

	if (capacity < TF_SMALL_STRING_SIZE)
	{
		string.capacity = TF_SMALL_STRING_SIZE;
		return string;
	}
	else
	{
		string.capacity = capacity;
		wchar_t* data = malloc(capacity * sizeof(wchar_t));
		if (data == NULL)
		{
			exit(1);
		}

		return string;
	}
}

_Must_inspect_result_ const wchar_t* TF_StringData(_In_ const TF_String* str)
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

void TF_StringDestroy(_In_ TF_String* str)
{
	if (str->length > TF_SMALL_STRING_SIZE)
	{
		free(GetDataPtr(str));
	}
}

void TF_StringAppend(_Inout_ TF_String* str, _In_ const TF_String* other)
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

void TF_StringResize(_Inout_ TF_String* str, _In_ size_t capacity)
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
