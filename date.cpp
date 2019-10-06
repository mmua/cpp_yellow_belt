//
// Created by Мороз Максим on 06/10/2019.
//

#include <sstream>
#include <iomanip>
#include "date.h"

bool operator<(const Date& lhs, const Date& rhs) {
    if(lhs.GetYear() == rhs.GetYear()) {
        if(lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    } else {
        return lhs.GetYear() < rhs.GetYear();
    }
}

void skip_sep(std::istream& stream, char sep) {
    if(stream.peek() != sep) {
        throw std::invalid_argument("Wrong date format");
    }
    stream.ignore(1);
}

std::istream& operator>>(std::istream& stream, Date& date)
{
    std::string date_value;
    getline(stream, date_value, ' ');

    try {
        std::istringstream date_stream(date_value);

        int year;
        int month;
        int day;

        date_stream.seekg(0);

        if (!(date_stream >> year)) {
            throw std::invalid_argument("Year");
        }
        skip_sep(date_stream, '-');

        if (!(date_stream >> month)) {
            throw std::invalid_argument("Month");
        }
        skip_sep(date_stream, '-');

        if (!(date_stream >> day)) {
            throw std::invalid_argument("Day");
        }

        std::string remain;
        if(date_stream >> remain) {
            throw std::invalid_argument("Remainder found");
        }

        // check day and month ranges
        if(month < 1 || month > 12) {
            throw std::domain_error("Month value is invalid: " + std::to_string(month));
        }

        if(day < 1 || day > 31) {
            throw std::domain_error("Day value is invalid: " + std::to_string(day));
        }

        date = Date(Year{year}, Month{month}, Day{day});
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Wrong date format: " + date_value);
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setw(4) << std::setfill('0') << date.GetYear()
           << "-" << std::setw(2) << date.GetMonth()
           << "-" << std::setw(2) << date.GetDay();
    return stream;
}