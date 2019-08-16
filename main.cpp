#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Forward declarations
template <typename T>
T Sqr(T val);

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& val);

template <typename K, typename V>
map<K, V> Sqr(const map<K, V>& val);

template <typename T>
vector<T> Sqr(const vector<T>& val);

// Implementation
template <typename T>
T Sqr(T val) {
    return val * val;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& val) {
    return {Sqr(val.first), Sqr(val.second)};
}

template <typename K, typename V>
map<K, V> Sqr(const map<K, V>& val) {
    map<K, V> res(val);
    for_each(begin(res), end(res), [](auto& p){p.second = Sqr(p.second);});
    return move(res);
}

template <typename T>
vector<T> Sqr(const vector<T>& val) {
    vector<T> res;
    res.reserve(val.size());
    transform(cbegin(val), cend(val), back_inserter(res), [](const auto& i) { return Sqr(i);});
    return move(res);
}

int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}
