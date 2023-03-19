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
	wchar_t* TF_StringData(TF_String*);
#ifdef __cplusplus
}
#endif