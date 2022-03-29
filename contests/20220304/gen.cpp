#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 1e4;
    cout << n << "\n";
std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= 8; ++j) cout << mtrnd() % 10;
        cout << "\n";
    }
}