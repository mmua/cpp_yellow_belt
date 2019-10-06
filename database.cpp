//
// Created by Мороз Максим on 06/10/2019.
//
#include <ostream>
#include <functional>

#include "database.h"

using namespace std;

class PrintEventVisitor: public EventVisitor {
public:
    PrintEventVisitor(ostream& os): os_(os) {};
    virtual void visitEvent(const Date& date, const std::string& event) const {
        os_ << date << " " << event << endl;
    };
private:
    ostream& os_;
};

Database& Database::Add(const Date& date, const std::string& event) {
    events[date].insert(event);
    return *this;
};

void Database::Print(std::ostream& stream) {
    PrintEventVisitor visitor(stream);
    accept(visitor);
}

size_t Database::Del(const Date &date) {
    size_t event_count = events.at(date).size();
    events.erase(date);
    return event_count;
}

size_t Database::delEvent(const Date& date, const std::string& event) {
    return events.at(date).erase(event);
};

std::set<std::string> Database::getEvents(const Date& date) const {
    return events.at(date);
};

void Database::accept(const EventVisitor& visitor) const {
    for(const auto& item: events) {
        for(const auto& event: item.second) {
            visitor.visitEvent(item.first, event);
        }
    }
}

int Database::RemoveIf(std::function<bool (const Date& date, const std::string& event)> pred) {
    return 0;
}

std::list<std::string> Database::FindIf(std::function<bool (const Date& date, const std::string& event)> pred) {
    return std::list<std::string &>();
}

std::string Database::Last(const Date &date) {
    return std::string();
};