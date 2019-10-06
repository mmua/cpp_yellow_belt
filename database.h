//
// Created by Мороз Максим on 06/10/2019.
//

#ifndef CPP_YELLOW_BELT_DATABASE_H
#define CPP_YELLOW_BELT_DATABASE_H

#include <map>
#include <set>
#include <string>
#include <list>

#include "date.h"

class EventVisitor {
public:
    virtual void visitEvent(const Date& date, const std::string& event) const = 0;
};

typedef bool (*Condition)(const Date& date, const std::string& event);

class Database {
public:
    Database& Add(const Date& date, const std::string& event);

    void Print(std::ostream& stream);

    size_t Del(const Date &date);

    size_t delEvent(const Date& date, const std::string& event);

    std::set<std::string> getEvents(const Date& date) const;

    int RemoveIf(std::function<bool (const Date& date, const std::string& event)> pred);

    std::list<std::string> FindIf(std::function<bool (const Date& date, const std::string& event)> pred);

    std::string Last(const Date& date);

    void accept(const EventVisitor& visitor) const;
private:
    std::map<Date, std::set<std::string> > events;
};

#endif //CPP_YELLOW_BELT_DATABASE_H
