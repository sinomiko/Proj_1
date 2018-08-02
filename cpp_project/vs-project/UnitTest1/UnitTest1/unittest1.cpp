#include "stdafx.h"
#include "CppUnitTest.h"
#include "Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
    TEST_CLASS(UnitTest1)
    {
    public:
        
        TEST_METHOD(TestMethod1)
        {
            int a = 2, b = 3;
            auto c = Calculator::Add(a, b);
            Assert::AreEqual(c, 5);
            // TODO: Your test code here
        }

    };
}