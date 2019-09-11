//
// Created by Мороз Максим on 2019-08-31.
//

#ifndef CPP_YELLOW_BELT_RESPONSES_H
#define CPP_YELLOW_BELT_RESPONSES_H
#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <utility>

using namespace std;

struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    // Наполните полями эту структуру
    vector<pair<string, vector<string> > > stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    // Наполните полями эту структуру
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
#endif //CPP_YELLOW_BELT_RESPONSES_H
