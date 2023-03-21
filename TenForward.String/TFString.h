#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

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
	TF_String TF_StringCreateEx(wchar_t* str, size_t length);

	/// <summary>
	/// Get a pointer to the underlying string data.
	/// </summary>
	/// <param name="str">The TF_String's data to examine.</param>
	/// <returns>A pointer to the data. This is not guaranteed to be null-terminated.</returns>
	const wchar_t* TF_StringData(const TF_String* str);

	/// <summary>
	/// Frees any underlying data associated with a TF_String.
	/// </summary>
	/// <param name="str">The TF_String to destroy.</param>
	void TF_StringDestroy(TF_String* str);

	/// <summary>
	/// Append a string to another string.
	/// </summary>
	/// <param name="str">The string to be appended to.</param>
	/// <param name="other">The string to append.</param>
	void TF_StringAppend(TF_String* str, const TF_String* other);

	/// <summary>
	/// Resize the reserved capacity of the string.
	/// </summary>
	/// <param name="str">The string to resize.</param>
	/// <param name="capacity">The number of characters that the string should be able to store.</param>
	void TF_StringResize(TF_String* str, size_t capacity);
#ifdef __cplusplus
}
#endif