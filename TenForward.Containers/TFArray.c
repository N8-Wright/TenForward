#include "pch.h"

TF_Array* TF_ArrayCreate(_In_ size_t size)
{
	return TF_ArrayCreateEx(size, TF_ARRAY_INITIAL_CAPACITY);
}

TF_Array* TF_ArrayCreateEx(_In_ size_t size, _In_ size_t capacity)
{
	const size_t additionalSize = size * capacity;
	TF_Array* array = malloc(sizeof(TF_Array) + additionalSize);
	if (array == NULL)
	{
		exit(1);
	}

	array->length = 0;
	array->capacity = capacity;
	return array;
}

void TF_ArrayDestroy(_In_ TF_Array* array)
{
	free(array);
}

void TF_ArrayResize(_Inout_ TF_Array** array, _In_ size_t size, _In_ size_t capacity)
{
	TF_Array* oldArray = *array;
	const size_t additionalSize = size * capacity;
	TF_Array* newArray = realloc(oldArray, sizeof(TF_Array) + additionalSize);
	if (newArray == NULL)
	{
		exit(1);
	}

	newArray->capacity = capacity;
	*array = newArray;
}

void TF_ArrayPush(_Inout_ TF_Array** array, _In_ size_t size, _In_ const void* item)
{
	size_t length = (*array)->length;
	size_t capacity = (*array)->capacity;

	if (length == capacity)
	{
		capacity *= 2;
		TF_ArrayResize(array, size, capacity);
	}

	char* data = (*array)->data;
	char* offset = data + (length * size);
	memcpy(offset, item, size);
	(*array)->length++;
}

void TF_ArrayPop(_In_ TF_Array* array, _In_ size_t size, _Out_opt_ void* item)
{
	if (array->length > 0)
	{
		array->length--;

		if (item != NULL)
		{
			char* offset = array->data + (array->length * size);
			memcpy(item, offset, size);
		}
	}
	else
	{
		item = NULL;
	}
}

void* TF_ArrayAt(_In_ TF_Array* array, _In_ size_t index, _In_ size_t size)
{
	if (index < array->length)
	{
		return array->data + (size * index);
	}
	else
	{
		return NULL;
	}
}
