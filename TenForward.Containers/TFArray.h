#pragma once
#include "TenForward.Common/Header.h"
#include <stdint.h>

TF_BEGIN_HEADER
#define TF_ARRAY_INITIAL_CAPACITY 12
typedef struct _TF_Array
{
	size_t length;
	size_t capacity;
	char data[];
} TF_Array;

/// <summary>
/// Create an array of default capacity.
/// </summary>
/// <param name="size">The size of the item that is intended to be stored.</param>
/// <returns>An allocated array object.</returns>
TF_Array* TF_ArrayCreate(_In_ size_t size);

/// <summary>
/// Create an array of variable capacity.
/// </summary>
/// <param name="size">The size of the item that is intended to be stored.</param>
/// <param name="capacity">The number of items that can be stored in the array.</param>
/// <returns>An allocated array object.</returns>
TF_Array* TF_ArrayCreateEx(_In_ size_t size, _In_ size_t capacity);

/// <summary>
/// Free the memory associated with an array.
/// </summary>
/// <param name="array">The array to destroy.</param>
void TF_ArrayDestroy(_In_ TF_Array* array);

/// <summary>
/// Resize an array to a different capacity.
/// </summary>
/// <param name="array">The array to resize</param>
/// <param name="size">The size of the item that is intended to be stored.</param>
/// <param name="capacity">The number of items that the array should be able to store.</param>
void TF_ArrayResize(_Inout_ TF_Array** array, _In_ size_t size, _In_ size_t capacity);

/// <summary>
/// Append an item to the end of an array.
/// </summary>
/// <param name="array">The array to append to.</param>
/// <param name="size">The size of the item that is intended to be stored.</param>
/// <param name="item">The item to append.</param>
void TF_ArrayPush(_Inout_ TF_Array** array, _In_ size_t size, _In_ const void* item);

/// <summary>
/// Remove the last item from the array.
/// </summary>
/// <param name="array">The array to modify.</param>
/// <param name="size">The size of the item that is intended to be stored.</param>
/// <param name="item">Optionally copy the removd item to this variable.</param>
void TF_ArrayPop(_In_ TF_Array* array, _In_ size_t size, _Out_opt_ void* item);
TF_END_HEADER
