#pragma once
#include "TenForward.Common/Header.h"
#include <stdint.h>

TF_BEGIN_HEADER

#if _WIN64
#define TF_SMALL_STRING_SIZE 25
#define TF_MAX_LENGTH INT64_MAX
#elif _WIN32
#define TF_SMALL_STRING_SIZE 29
#define TF_MAX_LENGTH INT_MAX
#endif

typedef struct _TF_String
{
	_Field_range_(0, TF_MAX_LENGTH)
	size_t length;

	union
	{
		struct _TF_SmallString
		{
			wchar_t data[TF_SMALL_STRING_SIZE];
		} smallStr;

		struct _TF_LongString
		{
			size_t capacity;
			wchar_t* data;
		} longStr;
	} impl;
} TF_String;

static_assert(sizeof(TF_String) == 64, "Sizeof string should be 64 bytes");

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
/// Gets the current capacity of the string.
/// </summary>
/// <param name="str">The string to examine.</param>
/// <returns>The capacity of the string.</returns>
_Check_return_ const size_t TF_StringCapacity(
	_In_ const TF_String* str);

/// <summary>
/// Gets the current length of the string.
/// </summary>
/// <param name="str">The string to examine.</param>
/// <returns>The length of the string.</returns>
_Check_return_ const size_t TF_StringLength(
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

/// <summary>
/// Create a new substring based on the provided input.
/// </summary>
/// <param name="str">The string to examine.</param>
/// <param name="startIndex">The index that will be the start of the substring.</param>
/// <returns>A substring containing the contents of the string from startIndex to the end of the string.</returns>
TF_String TF_StringSubstr(_In_ const TF_String* str, size_t startIndex);

/// <summary>
/// Create a new substring based on the provided input.
/// </summary>
/// <param name="str">The string to examine.</param>
/// <param name="startIndex">The index that will be the start of the substring.</param>
/// <param name="endIndex">The index that will be the end of the substring.</param>
/// <returns>A substring containing the cotents of the string from startIndex to endIndex.</returns>
TF_String TF_StringSubstrEx(_In_ const TF_String* str, size_t startIndex, size_t endIndex);
TF_END_HEADER