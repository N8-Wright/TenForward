#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TFStringTests
{
	TEST_CLASS(TFStringTests)
	{
	public:
		void ArraysAreEqual(const wchar_t *expected, const wchar_t *str, size_t length)
		{
			for (size_t i = 0; i < length; i++)
			{
				Assert::AreEqual(expected[i], str[i]);
			}
		}

		TEST_METHOD(CreateSmallString)
		{
			wchar_t test[] = L"Hello";
			size_t length = sizeof(test) / sizeof(test[0]) - 1;
			TF_String str = TF_StringCreateEx(test, length);

			Assert::AreEqual(str.length, length);
			Assert::AreEqual(str.capacity, (size_t)TF_SMALL_STRING_SIZE);
			ArraysAreEqual(test, str.data, length);
		}

		TEST_METHOD(CreateLargerString)
		{
			wchar_t test[] = L"This is a much larger string that won't get put in optimized stack";
			size_t length = sizeof(test) / sizeof(test[0]) - 1;
			TF_String str = TF_StringCreateEx(test, length);

			Assert::AreEqual(str.length, length);
			Assert::AreEqual(str.capacity, length);
			ArraysAreEqual(test, TF_StringData(&str), length);

			TF_StringDestroy(&str);
		}

		TEST_METHOD(AppendString_SmallToLarge)
		{
			wchar_t test1[] = L"Hello";
			size_t length1 = sizeof(test1) / sizeof(test1[0]) - 1;
			TF_String str1 = TF_StringCreateEx(test1, length1);


			wchar_t test2[] = L" World! This is a test append.";
			size_t length2 = sizeof(test2) / sizeof(test2[0]) - 1;
			TF_String str2 = TF_StringCreateEx(test2, length2);

			TF_StringAppend(&str1, &str2);

			wchar_t expected[] = L"Hello World! This is a test append.";
			Assert::AreEqual(str1.length, length1 + length2);
			Assert::AreEqual(str1.capacity, length1 + length2);
			ArraysAreEqual(
				expected,
				TF_StringData(&str1),
				sizeof(expected) / sizeof(expected[0]) - 1);

			TF_StringDestroy(&str1);
			TF_StringDestroy(&str2);
		}
	};
}
