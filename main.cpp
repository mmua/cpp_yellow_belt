#include <iostream>
#include "test_runner.h"
#include "sum_reverse_sort.h"

using namespace std;

void TestSum()
{
    AssertEqual(Sum(3, 4), 7);
}

void TestReverse()
{
    AssertEqual(Reverse("Hello"), "olleH");
}

void TestSort()
{
    vector<int> nums = {1,3,2,4};
    vector<int> sorted = {1,2,3,4};
    Sort(nums);
    AssertEqual(nums, sorted);
}

int main() {
    TestRunner runner;
    runner.RunTest(TestSum, "Sum");
    runner.RunTest(TestReverse, "Reverse");
    runner.RunTest(TestSort, "Sort");

    return 0;
}
