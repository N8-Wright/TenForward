#include "pch.h"
#include "framework.h"

#define LONG_STRING_BYTE_SET 1

#ifdef _WIN64
#define TF_STRING_BYTE_MARKER_MASK ((size_t)1 << 63)
#else
#define TF_STRING_BYTE_MARKER_MASK ((size_t)1 << 31)
#endif

_Check_return_ static inline bool IsSmall(_In_ const TF_String* str)
{
	return (str->length & TF_STRING_BYTE_MARKER_MASK) == 0;
}

static inline void SetLongBit(_In_ TF_String* str)
{
	str->length |= TF_STRING_BYTE_MARKER_MASK;
}

static inline void SetSmallBit(_In_ TF_String* str)
{
	str->length &= ~TF_STRING_BYTE_MARKER_MASK;
}

static inline size_t GetLongLength(_In_ const TF_String* str)
{
	return str->length & ~TF_STRING_BYTE_MARKER_MASK;
}

static void TF_StringResizeSmall(_Inout_ TF_String* str, _In_ size_t capacity)
{
	wchar_t* originalData = str->impl.smallStr.data;
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

		memcpy(data, originalData, str->length * sizeof(wchar_t));

		str->impl.longStr.capacity = capacity;
		str->impl.longStr.data = data;
		SetLongBit(str);
	}
}

static void TF_StringResizeLong(_Inout_ TF_String* str, _In_ size_t capacity)
{
	wchar_t* originalData = str->impl.longStr.data;
	if (capacity <= TF_SMALL_STRING_SIZE)
	{
		memcpy(str->impl.smallStr.data, originalData, capacity * sizeof(wchar_t));
		str->length = capacity;
		free(originalData);
	}
	else
	{
		void* result = realloc(originalData, capacity * sizeof(wchar_t));
		if (result == NULL)
		{
			exit(1);
		}

		str->impl.longStr.data = result;
		str->impl.longStr.capacity = capacity;
	}
}

TF_String TF_StringCreateEx(
	_In_reads_(length) const wchar_t* str,
	_In_ size_t length)
{
	TF_String string = { 0 };
	string.length = length;

	if (length > TF_SMALL_STRING_SIZE)
	{
		SetLongBit(&string);
		string.impl.longStr.capacity = length;
		wchar_t* data = malloc(length * sizeof(wchar_t));
		if (data == NULL)
		{
			exit(1);
		}

		memcpy(data, str, length * sizeof(wchar_t));
		string.impl.longStr.data = data;
	}
	else
	{
		memcpy(string.impl.smallStr.data, str, length * sizeof(wchar_t));
	}

	return string;
}

TF_String TF_StringCreate(_In_ size_t capacity)
{
	TF_String string = { 0 };
	string.length = 0;

	if (capacity < TF_SMALL_STRING_SIZE)
	{
		return string;
	}
	else
	{
		string.impl.longStr.capacity = capacity;
		wchar_t* data = malloc(capacity * sizeof(wchar_t));
		if (data == NULL)
		{
			exit(1);
		}

		string.impl.longStr.data = data;
		SetLongBit(&string);
		return string;
	}
}

_Must_inspect_result_ const wchar_t* TF_StringData(_In_ const TF_String* str)
{
	if (IsSmall(str))
	{
		return str->impl.smallStr.data;
	}
	else
	{
		return str->impl.longStr.data;
	}
}

_Must_inspect_result_ const size_t TF_StringCapacity(_In_ const TF_String* str)
{
	if (IsSmall(str))
	{
		return TF_SMALL_STRING_SIZE;
	}
	else
	{
		return str->impl.longStr.capacity;
	}
}

_Must_inspect_result_ const size_t TF_StringLength(_In_ const TF_String* str)
{
	if (IsSmall(str))
	{
		return str->length;
	}
	else
	{
		return GetLongLength(str);
	}
}

void TF_StringDestroy(_In_ TF_String* str)
{
	if (!IsSmall(str))
	{
		free(str->impl.longStr.data);
	}
}

void TF_StringAppend(_Inout_ TF_String* str, _In_ const TF_String* other)
{
	size_t strLength;
	size_t otherLength;
	wchar_t* data;
	if (IsSmall(str))
	{
		strLength = str->length;
		otherLength = TF_StringLength(other);

		const size_t capacity = strLength + otherLength;
		if (capacity > TF_SMALL_STRING_SIZE)
		{
			TF_StringResizeSmall(str, capacity);
			data = str->impl.longStr.data;
			str->length = capacity;
			SetLongBit(str);
		}
		else
		{
			data = str->impl.smallStr.data;
			str->length = capacity;
		}
	}
	else
	{
		strLength = GetLongLength(str);
		otherLength = TF_StringLength(other);
		const size_t capacity = strLength + otherLength;
		if (capacity > str->impl.longStr.capacity)
		{
			TF_StringResizeLong(str, capacity);
		}
		
		str->length = capacity;
		SetLongBit(str);
		data = str->impl.longStr.data;
	}

	memcpy(&data[strLength], TF_StringData(other), otherLength * sizeof(wchar_t));
}

void TF_StringResize(_Inout_ TF_String* str, _In_ size_t capacity)
{
	if (IsSmall(str))
	{
		TF_StringResizeSmall(str, capacity);
	}
	else
	{
		TF_StringResizeLong(str, capacity);
	}
}

TF_String TF_StringSubstr(_In_ const TF_String* str, size_t startIndex)
{
	return TF_StringSubstrEx(str, startIndex, TF_StringLength(str));
}

TF_String TF_StringSubstrEx(_In_ const TF_String* str, size_t startIndex, size_t endIndex)
{
	size_t substrSize = endIndex - startIndex;
	const wchar_t* data;
	if (IsSmall(str))
	{
		data = str->impl.smallStr.data;
	}
	else
	{
		data = str->impl.longStr.data;
	}

	return TF_StringCreateEx(data + startIndex, substrSize);
}
