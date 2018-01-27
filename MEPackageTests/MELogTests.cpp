#include "stdafx.h"
#include "CppUnitTest.h"
#include "MEPackageLib.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MELogTests
{
	TEST_CLASS(LogTests)
	{
	public:
		using LogType = MELog<4>;
		using ArrayType = std::array<char, 4>;

		TEST_METHOD(TestItLogsFullBufferFromZero) {
			LogType log;
			log.Log("123");
			Assert::IsTrue(ArrayType({ '1', '2', '3', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 3ULL);
			Assert::AreEqual(log.String(), std::string("123"));
		}

		TEST_METHOD(TestItLogsEmptyString) {
			LogType log;
			Assert::IsTrue(ArrayType({ ' ', ' ', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 0ULL);
			Assert::AreEqual(log.String(), std::string(""));
			log.Log("");
			Assert::IsTrue(ArrayType({ ' ', ' ', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 0ULL);
			Assert::AreEqual(log.String(), std::string(""));
		}

		TEST_METHOD(TestItLogsSingleChar) {
			LogType log;
			Assert::IsTrue(ArrayType({ ' ', ' ', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 0ULL);
			Assert::AreEqual(log.String(), std::string(""));
			log.Log("1");
			Assert::IsTrue(ArrayType({ '1', ' ', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 1ULL);
			Assert::AreEqual(log.String(), std::string("1"));
			log.Log("2");
			Assert::IsTrue(ArrayType({ '1', '2', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 2ULL);
			Assert::AreEqual(log.String(), std::string("12"));
			log.Log("3");
			Assert::IsTrue(ArrayType({ '1', '2', '3', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 3ULL);
			Assert::AreEqual(log.String(), std::string("123"));
			log.Log("4");
			Assert::IsTrue(ArrayType({ '1', '2', '3', '4' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("1234"));
			log.Log("5");
			Assert::IsTrue(ArrayType({ '5', '2', '3', '4' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 1ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("2345"));
			log.Log("6");
			Assert::IsTrue(ArrayType({ '5', '6', '3', '4' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 2ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("3456"));
			log.Log("7");
			Assert::IsTrue(ArrayType({ '5', '6', '7', '4' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 3ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("4567"));
			log.Log("8");
			Assert::IsTrue(ArrayType({ '5', '6', '7', '8' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("5678"));
			log.Log("9");
			Assert::IsTrue(ArrayType({ '9', '6', '7', '8' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 1ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("6789"));
		}

		TEST_METHOD(TestItLogsTwoChars) {
			LogType log;
			Assert::IsTrue(ArrayType({ ' ', ' ', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 0ULL);
			Assert::AreEqual(log.String(), std::string(""));
			log.Log("12");
			Assert::IsTrue(ArrayType({ '1', '2', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 2ULL);
			Assert::AreEqual(log.String(), std::string("12"));
			log.Log("34");
			Assert::IsTrue(ArrayType({ '1', '2', '3', '4' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("1234"));
			log.Log("56");
			Assert::IsTrue(ArrayType({ '5', '6', '3', '4' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 2ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("3456"));
			log.Log("78");
			Assert::IsTrue(ArrayType({ '5', '6', '7', '8' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("5678"));
			log.Log("90");
			Assert::IsTrue(ArrayType({ '9', '0', '7', '8' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 2ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("7890"));
		}

		TEST_METHOD(TestItLogsThreeChars) {
			LogType log;
			Assert::IsTrue(ArrayType({ ' ', ' ', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 0ULL);
			Assert::AreEqual(log.String(), std::string(""));
			log.Log("123");
			Assert::IsTrue(ArrayType({ '1', '2', '3', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 3ULL);
			Assert::AreEqual(log.String(), std::string("123"));
			log.Log("456");
			Assert::IsTrue(ArrayType({ '5', '6', '3', '4' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 2ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("3456"));
			log.Log("789");
			Assert::IsTrue(ArrayType({ '9', '6', '7', '8' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 1ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("6789"));
			log.Log("012");
			Assert::IsTrue(ArrayType({ '9', '0', '1', '2' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("9012"));
		}

		TEST_METHOD(TestItLogsFourChars) {
			LogType log;
			Assert::IsTrue(ArrayType({ ' ', ' ', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 0ULL);
			Assert::AreEqual(log.String(), std::string(""));
			log.Log("1234");
			Assert::IsTrue(ArrayType({ '1', '2', '3', '4' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("1234"));
			log.Log("5678");
			Assert::IsTrue(ArrayType({ '5', '6', '7', '8' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("5678"));
			log.Log("9012");
			Assert::IsTrue(ArrayType({ '9', '0', '1', '2' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("9012"));
		}

		TEST_METHOD(TestItLogsFiveChars) {
			LogType log;
			Assert::IsTrue(ArrayType({ ' ', ' ', ' ', ' ' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 0ULL);
			Assert::AreEqual(log.String(), std::string(""));
			log.Log("12345");
			Assert::IsTrue(ArrayType({ '2', '3', '4', '5' }) == log.Buffer);
			Assert::AreEqual(log.Offset, 0ULL);
			Assert::AreEqual(log.Length, 4ULL);
			Assert::AreEqual(log.String(), std::string("2345"));
		}
	};
}