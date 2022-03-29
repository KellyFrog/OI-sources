#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

mt19937_64 mtrnd(chrono::system_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int a = mtrnd() % 10 + 1;
    int b = mtrnd() % 10 + 1;
    cout << a << " " << b << "\n";
    int m = mtrnd() % 20 + 1;
    cout << m << "\n";
    rep(i, 1, m) {
	cout << mtrnd() % a + 1 << " " << mtrnd() % b + 1 << "\n";
    }
    
    return 0;
}
