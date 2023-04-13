#pragma once
#include "TenForward.Common/Header.h"
#include "TFDictionary.h"
#include "TFString.h"

TF_BEGIN_HEADER

size_t TF_DictHash_Int(_In_ _Notnull_ void* key);
bool TF_DictEqual_Int(_In_ _Notnull_ void* left, _In_ _Notnull_ void* right);

TF_END_HEADER
