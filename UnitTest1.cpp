#include "pch.h"
#include "CppUnitTest.h"
#include "shipment.h"
#include "mapping.h"
#include "Shipment.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestValidWeight)
        {
            double size = M_SIZE;
            double weight = 500;
            struct Point destination = { 12, 12 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMinimumWeight)
        {
            double size = S_SIZE;
            double weight = 1;
            struct Point destination = { 0, 0 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMaximumWeight)
        {
            double size = L_SIZE;
            double weight = 1000;
            struct Point destination = { 24, 24 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestSmallSize)
        {
            double size = S_SIZE;
            double weight = 100;
            struct Point destination = { 5, 5 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMediumSize)
        {
            double size = M_SIZE;
            double weight = 250;
            struct Point destination = { 10, 10 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestLargeSize)
        {
            double size = L_SIZE;
            double weight = 750;
            struct Point destination = { 15, 15 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMinimumDestination)
        {
            double size = M_SIZE;
            double weight = 300;
            struct Point destination = { 0, 0 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMaximumDestination)
        {
            double size = M_SIZE;
            double weight = 300;
            struct Point destination = { 24, 24 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMaximumValidDestination)
        {
            double size = M_SIZE;
            double weight = 300;
            struct Point destination = { 25, 25 };  // Maximum valid coordinates
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMinimumValidDestination)
        {
            double size = M_SIZE;
            double weight = 300;
            struct Point destination = { 1, 1 };  // Minimum valid coordinates
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestValidDestinationOnBuilding)
        {
            double size = M_SIZE;
            double weight = 300;
            struct Point destination = { 1, 1 };  // Assuming this is a valid building location
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestExitCode)
        {
            double size = 0;
            double weight = 0;
            struct Point destination = { 'x', 0 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestWeightJustUnderMax)
        {
            double size = M_SIZE;
            double weight = 999.99;
            struct Point destination = { 12, 12 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestWeightJustAboveMin)
        {
            double size = M_SIZE;
            double weight = 1.01;
            struct Point destination = { 12, 12 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestDestinationTopLeft)
        {
            double size = M_SIZE;
            double weight = 500;
            struct Point destination = { 0, 0 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestDestinationBottomRight)
        {
            double size = M_SIZE;
            double weight = 500;
            struct Point destination = { 24, 24 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestDestinationMiddle)
        {
            double size = M_SIZE;
            double weight = 500;
            struct Point destination = { 12, 12 };
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestDestinationValid)
        {
            double size = M_SIZE;
            double weight = 500;
            struct Point destination = { 3, 2 };  // Known valid point from earlier test cases
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMinimumValidDestination)
        {
            double size = M_SIZE;
            double weight = 300;
            struct Point destination = { 1, 1 };  // Minimum valid coordinates
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMaximumValidDestination)
        {
            double size = M_SIZE;
            double weight = 300;
            struct Point destination = { 25, 25 };  // Maximum valid coordinates
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMinimumWeight)
        {
            double size = S_SIZE;
            double weight = 1;
            struct Point destination = { 3, 2 };  // Known valid point
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMaximumWeight)
        {
            double size = L_SIZE;
            double weight = 1000;
            struct Point destination = { 3, 2 };  // Known valid point
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestSmallSize)
        {
            double size = S_SIZE;
            double weight = 100;
            struct Point destination = { 3, 2 };  // Known valid point
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestMediumSize)
        {
            double size = M_SIZE;
            double weight = 250;
            struct Point destination = { 3, 2 };  // Known valid point
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestLargeSize)
        {
            double size = L_SIZE;
            double weight = 750;
            struct Point destination = { 3, 2 };  // Known valid point
            int result = validate(size, weight, destination);
            Assert::AreEqual(1, result);
        }

    };
}