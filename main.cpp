#include <iostream>
#include "test_runner.h"
#include "phone_number.h"

using namespace std;

void TestPositive()
{
    PhoneNumber number1("+7-495-111-22-33");
    AssertEqual(number1.GetCountryCode(), "7");
    AssertEqual(number1.GetCityCode(), "495");
    AssertEqual(number1.GetLocalNumber(), "111-22-33");
    AssertEqual(number1.GetInternationalNumber(), "+7-495-111-22-33");

    PhoneNumber number2("+7-495-1112233");
    AssertEqual(number2.GetLocalNumber(), "1112233");

    PhoneNumber number3("+1-2-coursera-cpp");
    AssertEqual(number3.GetLocalNumber(), "coursera-cpp");
}

void TestNegative()
{
    try {
        PhoneNumber number("1-2-333");
        Assert(false, "некорректный номер - не начинается на '+'");
    }
    catch (const invalid_argument& e) {

    }
    try {
        PhoneNumber number("+7-1233");
        Assert(false, "некорректный номер - есть только код страны и города");
    }
    catch (const invalid_argument& e) {

    }
    try {
        PhoneNumber number("+7--1233");
        Assert(false, "некорректный номер - нет кода страны");
    }
    catch (const invalid_argument& e) {

    }

}

int main() {
    TestRunner runner;
    runner.RunTest(TestPositive, "Positive examples");
    runner.RunTest(TestNegative, "Negative examples");
    return 0;
}
