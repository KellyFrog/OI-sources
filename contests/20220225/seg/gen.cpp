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

    int n = 1e5, tp = 0;
    cout << n << " " << tp << "\n";
    rep(i, 2, n) {
	cout << i << " " << mtrnd() % (i-1) + 1 << " " << mtrnd() % (int)1e9 + 1 << "\n";
    }
    int q = 1e5;
    cout << q << "\n";
    while(q--) {
	int l, r, x;
	l = mtrnd() % n + 1;
	r = mtrnd() % n + 1;
	if(l > r) swap(l, r);
	int cnt = 0;
	do {
	    x = mtrnd() % n + 1;
	} while(l <= x && x <= r && ++cnt <= 100);
	cout << l << " " << r << " " << x << "\n";
    }

    return 0;
}
