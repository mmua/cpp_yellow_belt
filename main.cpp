#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
vector<string> SplitIntoWords(const string& s)
{
    vector<string> res;
    if(s.empty())
        return res;

    auto b = s.begin();
    auto it = find_if(b, end(s), [](const auto& c){return c == ' ';});
    res.emplace_back(string(b, it));

    while (it != end(s)) {
        b = it + 1;
        it  = find_if(b, end(s), [](const auto& c){return c == ' ';});
        res.emplace_back(string(b, it));
    }

    return move(res);
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
