#pragma once
#include "TenForward.Common/Header.h"
#include "TFArray.h"
#include <stdbool.h>
#include <stdint.h>

TF_BEGIN_HEADER

/// <summary>
/// Hash function that can be used to determine where an item should be placed in the backing array.
/// </summary>
typedef size_t(*TF_DictHash)(void* item);

/// <summary>
/// Fallback function to determine equality when two values' hashes match.
/// </summary>
typedef bool(*TF_DictEqual)(void* left, void* right);

typedef struct _TF_DictBucket
{
	void* key;
	void* value;
	struct _TF_DictBucket* next;
} TF_DictBucket;

typedef struct _TF_Dict
{
	TF_DictHash hash;
	TF_DictEqual equal;

	/// <summary>
	/// The number of key/value pairs stored in the dictionary
	/// </summary>
	size_t length;

	/// <summary>
	/// The capacity of the backing array of buckets.
	/// </summary>
	size_t bucketsCapacity;
	TF_DictBucket** buckets;
} TF_Dict;

TF_Dict TF_DictCreate(_In_ size_t capacity, _In_ TF_DictHash hash, _In_ TF_DictEqual equal);
void TF_DictAddOrUpdate(_In_ TF_Dict* dict, _In_ void* key, _In_ void* value);
TF_END_HEADER
