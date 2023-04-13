#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Containers
{
	TEST_CLASS(TFDictionaryTests)
	{
		TEST_METHOD(AddOrUpdate_AddOnePair_LengthUpdated)
		{
			TF_Dict dict = TF_DictCreate(5, TF_DictHash_Int, TF_DictEqual_Int);

			int key = 10;
			int value = 12;
			TF_DictAddOrUpdate(&dict, &key, &value);

			Assert::AreEqual((size_t)1, dict.length);
		}

		TEST_METHOD(AddOrUpdate_UpdateOnePair_LengthUnchanged)
		{
			TF_Dict dict = TF_DictCreate(5, TF_DictHash_Int, TF_DictEqual_Int);

			int key = 10;
			int value1 = 12;
			int value2 = 13;
			TF_DictAddOrUpdate(&dict, &key, &value1);
			TF_DictAddOrUpdate(&dict, &key, &value2);

			Assert::AreEqual((size_t)1, dict.length);
		}

		TEST_METHOD(AddOrUpdate_InsertMultipleNodesIntoSameBucket_LengthUpdated)
		{
			TF_Dict dict = TF_DictCreate(1, TF_DictHash_Int, TF_DictEqual_Int);

			int key1 = 19;
			int value1 = 99;

			int key2 = 22;
			int value2 = 108;

			TF_DictAddOrUpdate(&dict, &key1, &value1);
			TF_DictAddOrUpdate(&dict, &key2, &value2);

			Assert::AreEqual((size_t)2, dict.length);
		}
	};
}