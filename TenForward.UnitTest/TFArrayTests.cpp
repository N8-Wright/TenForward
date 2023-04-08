#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Containers
{
	TEST_CLASS(TFArrayTests)
	{
	public:
		TEST_METHOD(CreateArray)
		{
			TF_Array* array = TF_ArrayCreate(sizeof(int));

			Assert::AreEqual((size_t)0, array->length);
			Assert::AreEqual((size_t)TF_ARRAY_INITIAL_CAPACITY, array->capacity);
			TF_ArrayDestroy(array);
		}

		TEST_METHOD(CreateArrayWithDifferentCapacity)
		{
			TF_Array* array = TF_ArrayCreateEx(sizeof(char), 100);

			Assert::AreEqual((size_t)0, array->length);
			Assert::AreEqual((size_t)100, array->capacity);
			TF_ArrayDestroy(array);
		}

		TEST_METHOD(ResizeArray_LargerSize)
		{
			TF_Array* array = TF_ArrayCreate(sizeof(size_t));
			TF_ArrayResize(&array, sizeof(size_t), 123);

			Assert::AreEqual((size_t)0, array->length);
			Assert::AreEqual((size_t)123, array->capacity);
			TF_ArrayDestroy(array);
		}

		TEST_METHOD(ResizeArray_SmallerSize)
		{
			TF_Array* array = TF_ArrayCreateEx(sizeof(size_t), 123);
			TF_ArrayResize(&array, sizeof(size_t), 2);

			Assert::AreEqual((size_t)0, array->length);
			Assert::AreEqual((size_t)2, array->capacity);
			TF_ArrayDestroy(array);
		}

		TEST_METHOD(Push_ResizesAfterCapacityIsReached)
		{
			TF_Array* array = TF_ArrayCreateEx(sizeof(size_t), 2);
			
			size_t item = 10;
			TF_ArrayPush(&array, sizeof(size_t), &item);
			TF_ArrayPush(&array, sizeof(size_t), &item);
			TF_ArrayPush(&array, sizeof(size_t), &item);

			Assert::AreEqual((size_t)3, array->length);
			Assert::IsTrue(array->capacity > 2);
			TF_ArrayDestroy(array);
		}
	};
}
