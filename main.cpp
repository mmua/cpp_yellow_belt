#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        last_names[year] = last_name;
    }

    string GetFirstName(int year) const
    {
        return getName(year, first_names);
    }

    string GetLastName(int year) const
    {
        return getName(year, last_names);
    }

    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year
        string first_name, last_name;
        first_name = GetFirstName(year);
        last_name = GetLastName(year);

        if (!first_name.empty() && !last_name.empty()) {
            return first_name + " " + last_name;
        } else if (!first_name.empty()) {
            return first_name + " with unknown last name";
        } else if (!last_name.empty()) {
            return last_name + " with unknown first name";
        } else {
            return "Incognito";
        }
    }

    static string getName(int year, const map<int, string>& name) {
        if (name.empty())
            return "";
        auto iter = name.upper_bound(year);
        if (iter == begin(name)) {
            return "";
        }
        --iter;
        return iter->second;
    }
private:
    // приватные поля
    map<int, string> first_names;
    map<int, string> last_names;
};

void TestIncognito()
{
    Person person;
    AssertEqual(person.GetFullName(1978), "Incognito");
    person.ChangeFirstName(1979, "Maxim");
    person.ChangeLastName(1979, "Moroz");
    AssertEqual(person.GetFullName(1978), "Incognito");
    Assert(person.GetFullName(1979) != "Incognito", "Unexpected");
}

void TestUnknownFirstName()
{
    Person person;
    person.ChangeLastName(1986, "Marova");
    person.ChangeLastName(2019, "Moroz");
    AssertEqual(person.GetFullName(1977), "Incognito");
    AssertEqual(person.GetFullName(1985), "Incognito");
    AssertEqual(person.GetFullName(1986), "Marova with unknown first name");
    AssertEqual(person.GetFullName(1999), "Marova with unknown first name");
    AssertEqual(person.GetFullName(2019), "Moroz with unknown first name");
    AssertEqual(person.GetFullName(2029), "Moroz with unknown first name");
}

void TestUnknownLastName()
{
    Person person;
    person.ChangeFirstName(1978, "Olga");
    person.ChangeFirstName(2001, "Kolga");
    AssertEqual(person.GetFullName(1965), "Incognito");
    AssertEqual(person.GetFullName(1977), "Incognito");
    AssertEqual(person.GetFullName(1978), "Olga with unknown last name");
    AssertEqual(person.GetFullName(1980), "Olga with unknown last name");
    AssertEqual(person.GetFullName(2001), "Kolga with unknown last name");
    AssertEqual(person.GetFullName(2029), "Kolga with unknown last name");}

void TestFirstNameLastName() {
    Person person;
    person.ChangeLastName(1986, "Marova");
    person.ChangeFirstName(1986, "Olga");
    person.ChangeFirstName(1996, "Helga");
    person.ChangeFirstName(2001, "Olga");
    person.ChangeLastName(2019, "Moroz");

    AssertEqual(person.GetFullName(1965), "Incognito");
    AssertEqual(person.GetFullName(1986), "Olga Marova");
    AssertEqual(person.GetFullName(1990), "Olga Marova");
    AssertEqual(person.GetFullName(1996), "Helga Marova");
    AssertEqual(person.GetFullName(2001), "Olga Marova");
    AssertEqual(person.GetFullName(2018), "Olga Marova");
    AssertEqual(person.GetFullName(2019), "Olga Moroz");
    AssertEqual(person.GetFullName(2029), "Olga Moroz");
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestIncognito, "Test Incognito");
    runner.RunTest(TestUnknownFirstName, "Test Unknown First Name");
    runner.RunTest(TestUnknownLastName, "Test Unknown Last Name");
    runner.RunTest(TestFirstNameLastName, "Test First Name Last Name");
        Person person;

        person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1967, "Sergeeva");
        for (int year : {1900, 1965, 1990}) {
            cout << person.GetFullName(year) << endl;
        }

        person.ChangeFirstName(1970, "Appolinaria");
        for (int year : {1969, 1970}) {
            cout << person.GetFullName(year) << endl;
        }

        person.ChangeLastName(1968, "Volkova");
        for (int year : {1969, 1970}) {
            cout << person.GetFullName(year) << endl;
        }


    return 0;
}