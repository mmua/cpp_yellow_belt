//
// Created by Мороз Максим on 2019-09-01.
//
#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if(r.stops.empty()) {
        os << "No bus";
    }
    else {
        bool first = true;
        for (const auto& [stop, buses] : r.stops) {
            if(!first) {
                os << endl;
            } else {
                first = false;
            }
            os << "Stop " << stop << ": ";
            if (buses.empty()) {
                os << "no interchange";
            } else {
                for (const string& other_bus : buses) {
                    os << other_bus << " ";
                }
            }
        }
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.buses_to_stops.empty()) {
        os << "No buses";
    } else {
        bool first = true;
        for (const auto& [bus, stops] : r.buses_to_stops) {
            if(!first) {
                os << endl;
            } else {
                first = false;
            }
            os << "Bus " << bus << ": ";
            for (const string& stop : stops) {
                os << stop << " ";
            }
        }
    }
    return os;
}