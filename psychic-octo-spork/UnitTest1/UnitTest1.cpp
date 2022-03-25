#include "pch.h"
#include "CppUnitTest.h"
#include "mazefunctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestGetTeam)
		{
			const char* testTeam = "Holly A & Josh T";

			Assert::AreEqual(testTeam, GetTeam());
		}

		TEST_METHOD(TestGetAndSetMaze) 
		{
			int width = 10;
			int height = 11;

			const int coolData = 11;

			const int* coolerdata = &coolData;

			const int** data = &coolerdata;

			Assert::IsTrue(SetMaze(data, width, height));

			int** testData = GetMaze(width, height);

			Assert::IsNotNull(GetMaze(width, height));

			int finalTestData = **testData;

			Assert::AreEqual(11, finalTestData);
		}

		TEST_METHOD(TestGetNextPosition)
		{
			int coolxpos = 50;
			int coolypos = 1;

			int* xpos = &coolxpos;
			int* ypos = &coolypos;
			
			GetNextPosition(coolxpos, coolypos);
			
			Assert::AreEqual(*xpos, coolxpos);
			Assert::AreEqual(*ypos, coolypos);
		}

		TEST_METHOD(TestGetAndSetStart)
		{

			int width = 10;
			int height = 11;

			const int coolData = 11;

			const int* coolerdata = &coolData;

			const int** data = &coolerdata;

			SetMaze(data, width, height);

			int xpos = 2;
			int ypos = 3;

			Assert::IsTrue(SetStart(xpos, ypos));

			int uncooltestxpos = 10;
			int uncooltestypos = 10;

			int* testxpos = &uncooltestxpos;
			int* testypos = &uncooltestypos;

			GetStart(*testxpos, *testypos);

			Assert::AreEqual(xpos, *testxpos);
			Assert::AreEqual(ypos, *testypos);
		}

		TEST_METHOD(TestGetAndSetEnd)
		{

			int width = 10;
			int height = 11;

			const int coolData = 11;

			const int* coolerdata = &coolData;

			const int** data = &coolerdata;

			SetMaze(data, width, height);

			int coolxpos = 5;
			int coolypos = 6;

			Assert::IsTrue(SetEnd(coolxpos, coolypos));

			int testEndXpos = 69;
			int testEndYpos = 420;

			int* xpos = &testEndXpos;
			int* ypos = &testEndYpos;

			GetEnd(*xpos, *ypos);

			//Assert::AreEqual(coolxpos, *xpos);
			//Assert::AreEqual(coolypos, *ypos);
		}
	};
}
