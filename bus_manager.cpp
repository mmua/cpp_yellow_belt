//
// Created by Мороз Максим on 2019-09-01.
//
#include "bus_manager.h"
#include "responses.h"

#include <vector>
#include <string>
#include <cassert>

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
    buses_to_stops[bus] = stops;
    for(const auto& stop: stops) {
        stops_to_buses[stop].push_back(bus);
    }
    assert(!buses_to_stops.empty());
    assert(!stops_to_buses.empty());
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
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

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
    // Реализуйте этот метод
    AllBusesResponse r = {buses_to_stops};
    return r;
}