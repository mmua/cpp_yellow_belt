//
// Created by Мороз Максим on 06/10/2019.
//

#ifndef CPP_YELLOW_BELT_NODE_H
#define CPP_YELLOW_BELT_NODE_H

#include "date.h"
#include <string>

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode: public Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const override { return true; };
};

class LogicalOperationNode : public Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const override { return false; };
};

class DateComparisonNode: public Node {
public:
    DateComparisonNode(Comparison cmp, const Date& date): cmp_(cmp), date_(date) {};
    virtual bool Evaluate(const Date& date, const string& event) const override { return false; };
protected:
    Comparison cmp_;
    Date date_;
};

class EventComparisonNode: public Node {
public:
    EventComparisonNode(Comparison cmp, const std::string& event): cmp_(cmp), event_(event) {};
    virtual bool Evaluate(const Date& date, const string& event) const override { return false; };
protected:
    Comparison cmp_;
    std::string event_;
};

#endif //CPP_YELLOW_BELT_NODE_H
