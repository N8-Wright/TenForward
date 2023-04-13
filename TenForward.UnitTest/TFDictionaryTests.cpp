#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Containers
{
	TEST_CLASS(TFDictionaryTests)
	{
		TEST_METHOD(CanInsertIntoDictionary)
		{
			TF_Dict dict = TF_DictCreate(TF_DictHash_Int, TF_DictEqual_Int);

			int key = 10;
			char* value = "Hello world!";
			TF_DictInsert(&dict, &key, value);
		}
	};
}