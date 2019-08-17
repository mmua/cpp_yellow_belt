#include <iostream>
#include <map>

using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K, V>& col, const K& k)
{
    try {
        return col.at(k);
    }
    catch (const out_of_range& e) {
        throw runtime_error("Key error");
    }
}
int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
    return 0;
}
