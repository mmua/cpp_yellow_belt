#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
    // Реализуйте эту функцию
    return "";
}

void TestAll();
bool Predicate(const Date& date, const string& str)
{
    return false;
}
int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) -> bool {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(Predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
}
/****************************************/
//
//
//
//#include <fstream>
//#include <iostream>
//#include <sstream>
//
//#include <string>
//#include <map>
//#include <stdexcept>
//#include <iomanip>
//
//#include "date_ops.h"
//#include "event_db.h"
//
//using namespace std;
//
//class PrintEventVisitor: public EventVisitor {
//    virtual void visitEvent(const Date& date, const std::string& event) const {
//        cout << date << " " << event << endl;
//    };
//};
//
//typedef void (*command_fun)(Database& db, istream& stream);
//
//void cmd_add(Database& db, istream& stream)
//{
//    Date date;
//    string event;
//    stream >> date >> event;
//    db.addEvent(date, event);
//}
//
//void cmd_print(Database& db, istream& stream)
//{
//    PrintEventVisitor visitor;
//    db.accept(visitor);
//}
//
//void cmd_find(Database& db, istream& stream)
//{
//    Date date;
//    stream >> date;
//    try {
//        auto events = db.getEvents(date);
//        for (const auto& event: events) {
//            cout << event << endl;
//        }
//    }
//    catch (const out_of_range& e) {
//
//    }
//}
//
//void cmd_del(Database& db, istream& stream)
//{
//    Date date;
//    string event;
//    stream >> date;
//    if(stream >> event) {
//        try {
//            size_t removed = db.delEvent(date, event);
//            if(!removed) throw out_of_range("event not found");
//            cout << "Deleted successfully" << endl;
//        }
//        catch (const out_of_range& e) {
//            cout << "Event not found" << endl;
//        }
//    }
//    else {
//        size_t deleted = 0;
//        try {
//            deleted = db.delEvent(date);
//        }
//        catch (const out_of_range& e) {
//        }
//        cout << "Deleted " << deleted << " events" << endl;
//    }
//}
//int main()
//{
//    std::string line;
//    map<string, command_fun> ops = {{"Add",   cmd_add},
//                                    {"Print", cmd_print},
//                                    {"Del",   cmd_del},
//                                    {"Find",  cmd_find}};
//    Database storage;
//
//    while (getline(cin, line)) {
//        istringstream stream(line);
//        string command;
//
//        getline(stream, command, ' ');
//        if(command.empty()) continue;
//
//        command_fun op = nullptr;
//        try {
//            op = ops.at(command);
//        }
//        catch (const out_of_range& e) {
//            cout << "Unknown command: " << command << endl;
//            return 0;
//        }
//
//        try {
//            op(storage, stream);
//        } catch (const domain_error& e) {
//            cout << e.what() << endl;
//            return 0;
//        } catch (const invalid_argument& e) {
//            cout << e.what() << endl;
//            return 0;
//        }
//    }
//	return 0;
//}
