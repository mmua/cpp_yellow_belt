#include <iostream>
#include "test_runner.h"
#include "rectangle.h"

using namespace std;

void TestRectangle()
{
    Rectangle r(3,4);
    AssertEqual(r.GetPerimeter(), 14);
    AssertEqual(r.GetArea(), 12);
    AssertEqual(r.GetHeight(), 4);
    AssertEqual(r.GetWidth(), 3);
}
int main() {
    TestRunner runner;
    runner.RunTest(TestRectangle, "rectangle");
    return 0;
}
