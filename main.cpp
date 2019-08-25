#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Rational {
        public:
        Rational(): _numerator(0), _denominator(1) {};

        Rational(int numerator, int denominator) {
            if(denominator == 0) {
                throw invalid_argument("zero denominator");
            }
            if(numerator == 0) denominator = 1;
            int g = gcd(numerator, denominator);
            _numerator = numerator / g;
            _denominator = denominator / g;
            if (_denominator < 0) {
                _denominator = -_denominator;
                _numerator = -_numerator;
            }
        }

        int Numerator() const {
            return _numerator;
        }

        int Denominator() const {
            return _denominator;
        }

        bool operator==(const Rational& rhs) const
        {
            return (_numerator == rhs._numerator && _denominator == rhs._denominator);
        }

        Rational operator+(const Rational& rhs) const
        {
            int g = gcd(_denominator, rhs._denominator);
            int rhs_scale = _denominator / g;
            int lhs_scale = rhs._denominator / g;
            return Rational{lhs_scale * _numerator + rhs_scale * rhs._numerator, g * lhs_scale * rhs_scale};
        }

        Rational operator-(const Rational& rhs) const {
            Rational neg_rhs{-1 * rhs._numerator, rhs._denominator};
            return operator+(neg_rhs);
        }

        Rational operator*(const Rational& rhs) const {
            return Rational{_numerator * rhs._numerator, _denominator * rhs._denominator};
        }

        Rational operator/(const Rational& rhs) const {
            if(rhs.Numerator() == 0) {
                throw domain_error("zero divisor");
            }
            Rational rev_rhs = {rhs._denominator, rhs._numerator};
            return operator*(rev_rhs);
        }

        private:
        // Добавьте поля
        int _numerator;
        int _denominator;
};


void TestDefault()
{
    Rational r;
    AssertEqual(r.Numerator(), 0);
    AssertEqual(r.Denominator(), 1);
}

void TestNormalize()
{
    Rational r = {4, 6};
    AssertEqual(r.Numerator(), 2);
    AssertEqual(r.Denominator(), 3);
}

void TestSign()
{
    Rational r = {4, -6};
    AssertEqual(r.Numerator(), -2);
    AssertEqual(r.Denominator(), 3);

    Rational rp = {-4, -6};
    AssertEqual(rp.Numerator(), 2);
    AssertEqual(rp.Denominator(), 3);
}

void TestZero()
{
    Rational r = {0, -6};
    AssertEqual(r.Denominator(), 1);
    Rational rp = {0, 3};
    AssertEqual(rp.Denominator(), 1);
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestDefault, "Test Default");
    runner.RunTest(TestNormalize, "Normalize");
    runner.RunTest(TestSign, "Test Sign");
    runner.RunTest(TestZero, "Test Zero");
    return 0;
}