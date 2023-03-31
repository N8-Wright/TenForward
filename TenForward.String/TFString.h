#pragma once
#include "TenForward.Common/Header.h"
#include <stdint.h>

TF_BEGIN_HEADER

#if _WIN64
#define TF_SMALL_STRING_SIZE 8
#elif _WIN32
#define TF_SMALL_STRING_SIZE 12
#endif

typedef struct _TF_String
{
	size_t length;
	size_t capacity;
	wchar_t data[TF_SMALL_STRING_SIZE];
} TF_String;

static_assert(sizeof(TF_String) == 32, "Sizeof string should be 32 bytes");

/// <summary>
/// Initialize a string with an initial input.
/// </summary>
/// 
/// <param name="str">
/// Input to copy into the created TF_String. This does not have to be
/// null-terminated.
/// </param>
/// 
/// <param name="length">
/// The length of the str param. This should not include the null-terminated
/// byte.
/// </param>
/// 
/// <returns>An initialzed TF_String.</returns>
TF_String TF_StringCreateEx(
	_In_reads_(length) const wchar_t* str,
	_In_ size_t length);

TF_String TF_StringCreate(_In_ size_t capacity);

/// <summary>
/// Get a pointer to the underlying string data. This underlying data can
/// change if any modifiable operation happens to the string, so don't
/// keep this pointer around and assume it's stable.
/// </summary>
/// <param name="str">The TF_String's data to examine.</param>
/// <returns>A pointer to the data. This is not guaranteed to be null-terminated.</returns>
_Must_inspect_result_ const wchar_t* TF_StringData(
	_In_ const TF_String* str);

/// <summary>
/// Frees any underlying data associated with a TF_String.
/// </summary>
/// <param name="str">The TF_String to destroy.</param>
void TF_StringDestroy(_In_ TF_String* str);

/// <summary>
/// Append a string to another string.
/// </summary>
/// <param name="str">The string to be appended to.</param>
/// <param name="other">The string to append.</param>
void TF_StringAppend(_Inout_ TF_String* str, _In_ const TF_String* other);

/// <summary>
/// Resize the reserved capacity of the string.
/// </summary>
/// <param name="str">The string to resize.</param>
/// <param name="capacity">The number of characters that the string should be able to store.</param>
void TF_StringResize(_Inout_ TF_String* str, _In_ size_t capacity);
TF_END_HEADER