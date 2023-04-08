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

		TEST_METHOD(CreateEmptyString_SmallCapacity)
		{
			TF_String str = TF_StringCreate(1);
			
			Assert::AreEqual(TF_StringCapacity(&str), (size_t)TF_SMALL_STRING_SIZE);
			Assert::AreEqual(str.length, (size_t)0);
		}

		TEST_METHOD(CreateEmptyString_LargeCapacity)
		{
			TF_String str = TF_StringCreate(101);

			Assert::AreEqual(TF_StringCapacity(&str), (size_t)101);
			Assert::AreEqual(TF_StringLength(&str), (size_t)0);
		}

		TEST_METHOD(CreateSmallString)
		{
			wchar_t test[] = L"Hello";
			size_t length = sizeof(test) / sizeof(test[0]) - 1;
			TF_String str = TF_StringCreateEx(test, length);

			Assert::AreEqual(str.length, length);
			Assert::AreEqual(TF_StringCapacity(&str), (size_t)TF_SMALL_STRING_SIZE);
			ArraysAreEqual(test, TF_StringData(&str), length);
		}

		TEST_METHOD(CreateLargerString)
		{
			wchar_t test[] = L"This is a much larger string that won't get put in optimized stack";
			size_t length = sizeof(test) / sizeof(test[0]) - 1;
			TF_String str = TF_StringCreateEx(test, length);

			Assert::AreEqual(TF_StringLength(&str), length);
			Assert::AreEqual(TF_StringCapacity(&str), length);
			ArraysAreEqual(test, TF_StringData(&str), length);

			TF_StringDestroy(&str);
		}

		TEST_METHOD(AppendString_LargeAppendToSmall)
		{
			wchar_t test1[] = L"Hello";
			size_t length1 = sizeof(test1) / sizeof(test1[0]) - 1;
			TF_String str1 = TF_StringCreateEx(test1, length1);

			wchar_t test2[] = L" World! This is a test append. 123456789101112131415";
			size_t length2 = sizeof(test2) / sizeof(test2[0]) - 1;
			TF_String str2 = TF_StringCreateEx(test2, length2);

			TF_StringAppend(&str1, &str2);

			wchar_t expected[] = L"Hello World! This is a test append. 123456789101112131415";
			Assert::AreEqual(TF_StringLength(&str1), length1 + length2);
			Assert::AreEqual(TF_StringCapacity(&str1), length1 + length2);
			ArraysAreEqual(
				expected,
				TF_StringData(&str1),
				sizeof(expected) / sizeof(expected[0]) - 1);

			TF_StringDestroy(&str1);
			TF_StringDestroy(&str2);
		}

		TEST_METHOD(AppendString_SmallAppendToLarge)
		{
			wchar_t test1[] = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor "
				L"incididunt ut labore et dolore magna aliqua.Ut enim ad minim veniam, quis nostrud exercitation "
				L"ullamco laboris nisi ut aliquip ex ea commodo consequat.Duis aute irure dolor in reprehenderit "
				L"in voluptate velit esse cillum dolore eu fugiat nulla pariatur.Excepteur sint occaecat cupidatat "
				L"non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
			size_t length1 = sizeof(test1) / sizeof(test1[0]) - 1;
			TF_String str1 = TF_StringCreateEx(test1, length1);


			wchar_t test2[] = L" Small";
			size_t length2 = sizeof(test2) / sizeof(test2[0]) - 1;
			TF_String str2 = TF_StringCreateEx(test2, length2);

			TF_StringAppend(&str1, &str2);

			wchar_t expected[] = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor "
				L"incididunt ut labore et dolore magna aliqua.Ut enim ad minim veniam, quis nostrud exercitation "
				L"ullamco laboris nisi ut aliquip ex ea commodo consequat.Duis aute irure dolor in reprehenderit "
				L"in voluptate velit esse cillum dolore eu fugiat nulla pariatur.Excepteur sint occaecat cupidatat "
				L"non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Small";
			Assert::AreEqual(TF_StringLength(&str1), length1 + length2);
			Assert::AreEqual(TF_StringCapacity(&str1), length1 + length2);
			ArraysAreEqual(
				expected,
				TF_StringData(&str1),
				sizeof(expected) / sizeof(expected[0]) - 1);

			TF_StringDestroy(&str1);
			TF_StringDestroy(&str2);
		}

		TEST_METHOD(AppendString_SmallAppendToSmall)
		{
			wchar_t test1[] = L"Hello";
			size_t length1 = sizeof(test1) / sizeof(test1[0]) - 1;
			TF_String str1 = TF_StringCreateEx(test1, length1);


			wchar_t test2[] = L" World!";
			size_t length2 = sizeof(test2) / sizeof(test2[0]) - 1;
			TF_String str2 = TF_StringCreateEx(test2, length2);

			TF_StringAppend(&str1, &str2);

			wchar_t expected[] = L"Hello World!";
			Assert::AreEqual(TF_StringLength(&str1), length1 + length2);

			if (TF_StringCapacity(&str1) > TF_SMALL_STRING_SIZE)
			{
				Assert::AreEqual(TF_StringCapacity(&str1), length1 + length2);
			}
			else
			{
				Assert::AreEqual(TF_StringCapacity(&str1), (size_t)TF_SMALL_STRING_SIZE);
			}

			ArraysAreEqual(
				expected,
				TF_StringData(&str1),
				sizeof(expected) / sizeof(expected[0]) - 1);

			TF_StringDestroy(&str1);
			TF_StringDestroy(&str2);
		}

		TEST_METHOD(Resize_SmallToLarge)
		{
			wchar_t test[] = L"Test 😂";
			size_t testLength = sizeof(test) / sizeof(test[0]);
			TF_String str = TF_StringCreateEx(test, testLength);

			const size_t expectedLength = TF_StringLength(&str);
			TF_StringResize(&str, 100);
			Assert::AreEqual(TF_StringCapacity(&str), (size_t)100);
			Assert::AreEqual(TF_StringLength(&str), expectedLength);
			ArraysAreEqual(test, TF_StringData(&str), testLength);
		}

		TEST_METHOD(Resize_SmallToSmall)
		{
			wchar_t test[] = L"1";
			size_t testLength = sizeof(test) / sizeof(test[0]);
			TF_String str = TF_StringCreateEx(test, testLength);

			size_t expectedLength = str.length;
			TF_StringResize(&str, TF_SMALL_STRING_SIZE);
			Assert::AreEqual(TF_StringCapacity(&str), (size_t)TF_SMALL_STRING_SIZE);
			Assert::AreEqual(str.length, expectedLength);
			ArraysAreEqual(test, TF_StringData(&str), testLength);
		}

		TEST_METHOD(Resize_LargeToSmall)
		{
			wchar_t test[] = L"123456789_10_11_12_13_14 💕😁👍";
			size_t testLength = sizeof(test) / sizeof(test[0]);
			TF_String str = TF_StringCreateEx(test, testLength);

			TF_StringResize(&str, TF_SMALL_STRING_SIZE);
			Assert::AreEqual(TF_StringCapacity(&str), (size_t)TF_SMALL_STRING_SIZE);
			Assert::AreEqual(TF_StringLength(&str), (size_t)TF_SMALL_STRING_SIZE);

			// We expect that the data now stored in the string is truncated to test[0..TF_SMALL_STRING_SIZE]
			ArraysAreEqual(test, TF_StringData(&str), TF_SMALL_STRING_SIZE);
		}

		TEST_METHOD(Resize_LargeToLarge)
		{
			wchar_t test[] = L"00000000000000000000000000000000000000";
			size_t testLength = sizeof(test) / sizeof(test[0]);
			TF_String str = TF_StringCreateEx(test, testLength);

			size_t expectedLength = TF_StringLength(&str);
			size_t expectedCapacity = testLength * 2;
			TF_StringResize(&str, expectedCapacity);
			Assert::AreEqual(TF_StringCapacity(&str), expectedCapacity);
			Assert::AreEqual(TF_StringLength(&str), expectedLength);

			ArraysAreEqual(test, TF_StringData(&str), expectedLength);
		}

		TEST_METHOD(Substr_CreatesSubstrWithStartIndex)
		{
			wchar_t test[] = L"Hello world! 123456789";
			size_t testLength = sizeof(test) / sizeof(test[0]);
			TF_String str = TF_StringCreateEx(test, testLength);
			TF_String substr = TF_StringSubstr(&str, 13);

			wchar_t expected[] = L"123456789";
			size_t expectedLength = sizeof(expected) / sizeof(expected[0]);
			ArraysAreEqual(expected, TF_StringData(&substr), expectedLength);

			TF_StringDestroy(&str);
			TF_StringDestroy(&substr);
		}

		TEST_METHOD(Substr_CreatesSubstrWithStartAndEndIndex)
		{
			wchar_t test[] = L"Hello world! 123456789";
			size_t testLength = sizeof(test) / sizeof(test[0]);
			TF_String str = TF_StringCreateEx(test, testLength);
			TF_String substr = TF_StringSubstrEx(&str, 13, 16);

			wchar_t expected[] = L"123";
			size_t expectedLength = sizeof(expected) / sizeof(expected[0]);
			ArraysAreEqual(expected, TF_StringData(&substr), expectedLength);

			TF_StringDestroy(&str);
			TF_StringDestroy(&substr);
		}

		TEST_METHOD(Substr_StartIndexGreaterThanEndIndex_InvalidStringReturned)
		{
			wchar_t test[] = L"Test string";
			size_t length = sizeof(test) / sizeof(test[0]);

			TF_String str = TF_StringCreateEx(test, length);
			TF_String substr = TF_StringSubstrEx(&str, 2, 1);
			
			Assert::AreEqual(TF_StringLength(&substr), (size_t)0);
		}

		TEST_METHOD(Substr_Small_EndIndexGreaterThanStringLength_InvalidStringReturned)
		{
			wchar_t test[] = L"Test string";
			size_t length = sizeof(test) / sizeof(test[0]);

			TF_String str = TF_StringCreateEx(test, length);
			TF_String substr = TF_StringSubstrEx(&str, 0, length + 1);

			Assert::AreEqual(TF_StringLength(&substr), (size_t)0);
		}

		TEST_METHOD(Substr_Long_EndIndexGreaterThanStringLength_InvalidStringReturned)
		{
			wchar_t test[] = L"Test string. 123123123123123123123123123123123123123";
			size_t length = sizeof(test) / sizeof(test[0]);

			TF_String str = TF_StringCreateEx(test, length);
			TF_String substr = TF_StringSubstrEx(&str, 0, length + 1);

			Assert::AreEqual(TF_StringLength(&substr), (size_t)0);

			TF_StringDestroy(&str);
		}

		TEST_METHOD(Substr_Small_StartIndexGreaterThanStringLength_InvalidStringReturned)
		{
			wchar_t test[] = L"Test string";
			size_t length = sizeof(test) / sizeof(test[0]);

			TF_String str = TF_StringCreateEx(test, length);
			TF_String substr = TF_StringSubstr(&str, length + 1);

			Assert::AreEqual(TF_StringLength(&substr), (size_t)0);
		}

		TEST_METHOD(Substr_Long_StartIndexGreaterThanStringLength_InvalidStringReturned)
		{
			wchar_t test[] = L"Test string. 123123123123123123123123123123123123123";
			size_t length = sizeof(test) / sizeof(test[0]);

			TF_String str = TF_StringCreateEx(test, length);
			TF_String substr = TF_StringSubstr(&str, length + 1);

			Assert::AreEqual(TF_StringLength(&substr), (size_t)0);
		}
	};
}
