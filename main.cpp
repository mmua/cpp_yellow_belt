#include <iostream>

using namespace std;

int main() {
    unsigned n, density;
    cin >> n >> density;

    uint64_t mass = 0;
    for(unsigned i = 0; i < n; ++i) {
        unsigned width, height, depth;
        cin >> width >> height >> depth;
        mass += static_cast<uint64_t >(density) * width * height * depth;
    }

    cout << mass << endl;
    return 0;
}