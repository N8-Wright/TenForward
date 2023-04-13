#include "pch.h"

TF_Dict TF_DictCreate(_In_ TF_DictHash hash, _In_ TF_DictEqual equal)
{
	TF_Dict dict;
	dict.hash = hash;
	dict.equal = equal;

	dict.length = 0;
	dict.bucketsCapacity = 10;
	dict.buckets = calloc(10, sizeof(dict.buckets));
	return dict;
}

static bool TF_DictInsertIntoBucket(_In_ TF_DictEqual equal, _In_ TF_DictBucket** bucket, _In_ TF_DictBucket* node)
{
	TF_DictBucket* iter = *bucket;
	if (iter == NULL)
	{
		*bucket = node;
		return true;
	}
	else
	{
		while (iter != NULL)
		{
			if (equal(iter->key, node->key))
			{
				iter->key = node->key;
				iter->value = node->value;
				return false;
			}

			iter = iter->next;
		}

		return true;
	}
}

static TF_DictBucket* TF_DictCreateNode(_In_ void* key, _In_ void* value)
{
	TF_DictBucket* node = malloc(sizeof(TF_DictBucket));
	if (node == NULL)
	{
		exit(1);
	}

	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

void TF_DictAddOrUpdate(_In_ TF_Dict* dict, _In_ void* key, _In_ void* value, _In_ size_t keySize, _In_ size_t valueSize)
{
	size_t hash = dict->hash(key);

	TF_DictBucket* node = TF_DictCreateNode(key, value);
	if (TF_DictInsertIntoBucket(dict->equal, &dict->buckets[hash % dict->bucketsCapacity], node))
	{
		dict->length++;
	}
}