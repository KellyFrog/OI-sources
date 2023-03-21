// Problem: D - Decrementing
// Contest: AtCoder - AtCoder Grand Contest 010
// URL: https://atcoder.jp/contests/agc010/tasks/agc010_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 1e5 + 5;

int n, a[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	int p = 0;
	while(1) {
		bool f = 1;
		rep(i, 1, n) if(a[i] != 1) f = 0;
		if(f) {
			cout << (p ? "First" : "Second") << "\n";
			return 0;
		}
		int s = 0;
		rep(i, 1, n) s += (a[i] % 2 == 0);
		if(s % 2 == 1) {
			cout << (p ? "Second" : "First") << "\n";
			return 0;
		}
		int c = 0;
		rep(i, 1, n) c += (a[i] % 2 == 1);
		rep(i, 1, n) if(a[i] == 1) c = 2;
		if(c == 1) {
			p ^= 1;
			rep(i, 1, n) a[i] >>= 1;
			int g = a[1];
			rep(i, 1, n) g = __gcd(g, a[i]);
			rep(i, 1, n) a[i] /= g;
		} else {
			cout << (p ? "First" : "Second") << "\n";
			return 0;
		}
	}
	
	return 0;
}

