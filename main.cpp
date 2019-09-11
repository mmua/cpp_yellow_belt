#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
    auto it = find_if(numbers.cbegin(), numbers.cend(), [](const auto& el) { return el < 0;});
    copy( make_reverse_iterator(it), make_reverse_iterator(numbers.cbegin()), ostream_iterator<int>(cout, " "));
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}
