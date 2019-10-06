//
// Created by Мороз Максим on 2019-08-17.
//

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <utility>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

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

struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string> buses;
};

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

struct StopsForBusResponse {
    // Наполните полями эту структуру
    vector<pair<string, vector<string> > > stops;
};

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

struct AllBusesResponse {
    // Наполните полями эту структуру
    map<string, vector<string>> buses_to_stops;
};

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

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        buses_to_stops[bus] = stops;
        for(const auto& stop: stops) {
            stops_to_buses[stop].push_back(bus);
        }
        assert(!buses_to_stops.empty());
        assert(!stops_to_buses.empty());
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        BusesForStopResponse r;
        try {
            for (const string& bus : stops_to_buses.at(stop)) {
                r.buses.push_back(bus);
            }
        }
        catch (const out_of_range& e) {};
        return r;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        StopsForBusResponse r;
        try {
            for (const string &stop : buses_to_stops.at(bus)) {
                pair<string, vector<string>> stop_info = {stop, {}};
                for (const string &other_bus : stops_to_buses.at(stop)) {
                    if (bus != other_bus) {
                        stop_info.second.push_back(other_bus);
                    }
                }
                r.stops.push_back(stop_info);
            }
        }
        catch (const out_of_range& e) {};
        return r;
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        AllBusesResponse r = {buses_to_stops};
        return r;
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}