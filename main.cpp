#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int64_t> temperatures(n);
    int64_t sum = 0;
    for (auto & temperature : temperatures) {
        cin >> temperature;
        sum += temperature;
    }

    int64_t average = sum / n;

    vector<size_t> result_indices;
    for (size_t i = 0; i < temperatures.size(); ++i) {
        if (temperatures[i] > average) {
            result_indices.push_back(i);
        }
    }

    cout << result_indices.size() << endl;
    copy(result_indices.cbegin(), result_indices.cend(), ostream_iterator<size_t>(cout, " "));
    cout << endl;

    return 0;
}