//
// Created by Мороз Максим on 2019-08-31.
//
#include "query.h"

#include <iostream>
#include <map>

void input_new_bus(istream& is, Query& q) {
    string bus;
    is >> bus;
    int stop_count;
    is >> stop_count;
    q.bus = bus;
    q.stops.resize(stop_count);
    for (string& stop : q.stops) {
        is >> stop;
    }
}

void input_buses_for_stop(istream& is, Query& q) {
    is >> q.stop;
}

void input_stops_for_bus(istream& is, Query& q) {
    is >> q.bus;
}

void input_all_buses(istream& is, Query& q) {

}

using input_func = void (*)(istream& is, Query& q);

istream& operator >> (istream& is, Query& q) {
    static const map<string, QueryType> code_type_map = {{"NEW_BUS", QueryType::NewBus},
                                                         {"BUSES_FOR_STOP", QueryType::BusesForStop},
                                                         {"STOPS_FOR_BUS", QueryType::StopsForBus},
                                                         {"ALL_BUSES", QueryType::AllBuses}};
    static const map<QueryType , input_func> type_input_func = {
            {QueryType::NewBus, input_new_bus},
            {QueryType::BusesForStop, input_buses_for_stop},
            {QueryType::StopsForBus, input_stops_for_bus},
            {QueryType::AllBuses, input_all_buses},
    };
    // Реализуйте эту функцию
    string operation_code;
    is >> operation_code;
    try {
        q.type = code_type_map.at(operation_code);
        type_input_func.at(q.type)(is, q);
    }
    catch (const out_of_range& e) {
        cout << "invalid command " << e.what();
    }
    return is;
}
