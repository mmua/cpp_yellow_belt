//
// Created by Мороз Максим on 2019-09-01.
//

#ifndef CPP_YELLOW_BELT_BUS_MANAGER_H
#define CPP_YELLOW_BELT_BUS_MANAGER_H
#pragma once

#include "responses.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops);

    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const;

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

#endif //CPP_YELLOW_BELT_BUS_MANAGER_H
