//
// Created by Мороз Максим on 06/10/2019.
//

#ifndef CPP_YELLOW_BELT_DATE_H
#define CPP_YELLOW_BELT_DATE_H

#include <iostream>
struct Year {
    Year(int v): val(v) {};
    int val;
};

struct Month {
    Month(int v): val(v) {};
    int val;
};

struct Day {
    Day(int v): val(v) {};
    int val;
};

class Date {
public:
    Date(): _year(0), _month(0), _day(0) {
    }

    explicit Date(Year year, Month month, Day day): _year(year.val), _month(month.val), _day(day.val)
    {
        if(!(_month.val > 0 && _month.val < 13)) {
            throw std::domain_error("Month value is invalid: " + std::to_string(_month.val));
        }
        if(!(_day.val > 0 && _day.val < 32)) {
            throw std::domain_error("Day value is invalid: " + std::to_string(_day.val));
        }
    }

    int GetYear() const {
        return _year.val;
    }
    int GetMonth() const {
        return _month.val;
    }
    int GetDay() const {
        return _day.val;
    }

private:
    Year _year;
    Month _month;
    Day _day;
};

Date ParseDate(std::istream& stream);
bool operator<(const Date& lhs, const Date& rhs);
std::ostream& operator<<(std::ostream& stream, const Date& date);

#endif //CPP_YELLOW_BELT_DATE_H
