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

TF_Array* TF_ArrayCreate(_In_ size_t size);
TF_Array* TF_ArrayCreateEx(_In_ size_t size, _In_ size_t capacity);
void TF_ArrayDestroy(_In_ TF_Array* array);
void TF_ArrayResize(_Inout_ TF_Array** array, _In_ size_t size, _In_ size_t capacity);
void TF_ArrayPush(_Inout_ TF_Array** array, _In_ size_t size, _In_ const void* item);

TF_END_HEADER
