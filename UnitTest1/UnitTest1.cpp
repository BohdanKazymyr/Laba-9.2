#include "pch.h"
#include "CppUnitTest.h"
#include "../Laba 9.3/Laba 9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 1;
			Student* p = new Student[N];
			int ikurs = 1;
			Cours kurs = L;
			string prizv;
			int found = 1;
			int menuItem = 2;
			Create(p, N);
			Print(p, N);
			Sort(p, N);
		}
	};
}
