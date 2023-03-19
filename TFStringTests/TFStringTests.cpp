#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TFStringTests
{
	TEST_CLASS(TFStringTests)
	{
	public:
		void ArraysAreEqual(wchar_t *expected, wchar_t *str, size_t length)
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
			Assert::AreEqual(str.capacity, length);
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
		}
	};
}
