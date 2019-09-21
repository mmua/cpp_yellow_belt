#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main() {
    size_t n;
    vector<int> nums = {};

    cin >> n;
    nums.resize(n);

    for(size_t i = n; i > 0; --i) {
        nums[i - 1] = n - i + 1;
    }
    do {
        copy(begin(nums), end(nums), ostream_iterator<int>(cout, " "));
        cout << endl;
    } while (prev_permutation(begin(nums), end(nums)));
    return 0;
}
