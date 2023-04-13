#include "pch.h"

size_t TF_DictHash_Int(_In_ _Notnull_ void* key)
{
	int* value = key;
	return *value;
}

bool TF_DictEqual_Int(_In_ _Notnull_ void* left, _In_ _Notnull_ void* right)
{
	int* a = left;
	int* b = right;

	return *a == *b;
}