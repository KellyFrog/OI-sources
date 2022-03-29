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

    int n = 1e5, q = 1e5;
    cout << n << "\n";
    rep(i, 2, n) {
	cout << i << " " << mtrnd() % (i-1) + 1 << "\n";
    }
    rep(i, 1, n) cout << mtrnd() % (int)1e7 + 1 << " \n"[i == n];
    cout << q << "\n";
    rep(i, 1, q) {
	int u = mtrnd() % n + 1;
	int v = mtrnd() % n + 1;
	int x = mtrnd() % (int)1e7 + 1;
	cout << u << " " << v << " " << x << "\n";
    }
    
    return 0;
}
