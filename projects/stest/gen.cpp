#include <bits/stdc++.h>

using namespace std;

mt19937 mtrnd(chrono::system_clock::now().time_since_epoch().count());

int main() {
    cout << (mtrnd() & 15) << " " << (mtrnd() & 15) << "\n";
    return 0;
}
