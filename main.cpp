#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, const string& occupation): Name(name), Occupation(occupation) {};
    virtual void Walk(string destination) {
        cout << Occupation << ": " << Name << " walks to: " << destination << endl;
    };
    const string Name;
    const string Occupation;
};

class Student : public Person {
public:

    Student(const string& name, const string& favouriteSong) : Person(name, "Student"), FavouriteSong(favouriteSong) {
    }

    void Learn() {
        cout << Occupation << ": " << Name << " learns" << endl;
    }

    void Walk(string destination) override {
        Person::Walk(destination);
        cout << Occupation << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << Occupation << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string FavouriteSong;
};


class Teacher : public Person {
public:

    Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject) {
    }

    void Teach() {
        cout << Occupation << ": " << Name << " teaches: " << Subject << endl;
    }

public:
    string Subject;
};


class Policeman : public Person {
public:
    explicit Policeman(const string &name) : Person(name, "Policeman") {
    }

    void Check(Person& p) {
        cout << Occupation << ": " << Name << " checks " << p.Occupation << ". " << p.Occupation << "'s name is: " << p.Name << endl;
    }
};


void VisitPlaces(Person& person, const vector<string>& places) {
    for (auto p : places) {
        person.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
