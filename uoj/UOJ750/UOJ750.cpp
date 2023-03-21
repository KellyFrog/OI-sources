// Problem: A. 小火车
// Contest: UOJ - UOJ NOI Round #6 Day2
// URL: https://uoj.ac/contest/78/problem/750
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-08-07 08:55:29
// Input/Output: stdin/stdout
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

const int N = 44;
const int M = 1 << 20 | 5;

mt19937_64 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

int n, p[N], ans[N];
ll P;
ll a[N];
pair<ll, int> b[M], c[M];

bool solve() {
	shuffle(p + 1, p + n + 1, mtrnd);
	int n1 = n >> 1;
	int n2 = n - n1;
	int u1 = (1 << n1) - 1;
	int u2 = (1 << n2) - 1;
	rep(s, 0, u1) {
		ll sum = 0;
		rep(j, 1, n1) {
			if(s >> j-1 & 1) sum += a[p[j]];
		}
		sum %= P;
		b[s] = mp(sum, s);
	}
	rep(s, 0, u2) {
		ll sum = 0;
		rep(j, 1, n2) {
			if(s >> j-1 & 1) sum += a[p[j+n1]];
		}
		sum %= P;
		c[s] = mp(sum, s);
	}
	sort(b + 1, b + u1 + 1);
	sort(c + 1, c + u2 + 1);
	int p1 = 1, p2 = 1;
	while(p1 <= u1 && p2 <= u2) {
		if(b[p1].fi == c[p2].fi) {
			rep(i, 1, n1) if(b[p1].se >> i-1 & 1) ans[p[i]] = 1;
			rep(i, 1, n2) if(c[p2].se >> i-1 & 1) ans[p[i+n1]] = -1;
			rep(i, 1, n) cout << ans[i] << " \n"[i == n];
			return 1;
		}
		if(b[p1].fi < c[p2].fi) ++p1;
		else ++p2;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> P;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) p[i] = i;
	
	while(1) {
		if(solve()) return 0;
	}
	
	return 0;
}
