//
// Created by Мороз Максим on 2019-08-31.
//

#ifndef CPP_YELLOW_BELT_QUERY_H
#define CPP_YELLOW_BELT_QUERY_H
#pragma once

#include <string>
#include <vector>

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

istream& operator >> (istream& is, Query& q);

#endif //CPP_YELLOW_BELT_QUERY_H
