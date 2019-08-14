#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

tuple<string, string, map<Lang, string>, int64_t> get_comparator(const Region& region)
{
    return make_tuple(region.std_name, region.parent_std_name, region.names, region.population);
}
bool operator<(const Region& lhs, const Region& rhs){
    return get_comparator(lhs) <
            get_comparator(rhs);
}
int FindMaxRepetitionCount(const vector<Region>& regions)
{
    if(regions.empty()) return 0;
    map<Region, int> region_count;
    for(const auto& region: regions) {
        region_count[region] += 1;
    }
    auto p = max_element(begin(region_count), end(region_count), [](const auto& a, const auto& b){ return a.second < b.second;});
    return p->second;
}
