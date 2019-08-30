//
// Created by Мороз Максим on 2019-08-30.
//
#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number)
{
    istringstream istream(international_number);
    if(istream.peek() != '+') {
        throw invalid_argument("Missing plus sign");
    }
    istream.ignore(1);
    getline(istream, country_code_, '-');
    getline(istream, city_code_, '-');
    getline(istream, local_number_);
    if(local_number_.empty() || city_code_.empty() || country_code_.empty()) {
        throw invalid_argument("Missing part");
    }
}

string PhoneNumber::GetCountryCode() const{
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    ostringstream ostream;
    ostream << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
    return ostream.str();
}
