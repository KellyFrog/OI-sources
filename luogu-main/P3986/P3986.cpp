// Problem: P3986 斐波那契数列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3986
// Memory Limit: 500 MB
// Time Limit: 1000 ms
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

const int N = 105;
const int P = 1e9 + 7;

int m = 45;
ll f1[N], f2[N];

inline ll exgcd(ll a, ll b, ll& x, ll& y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	ll tx, ty;
	ll g = exgcd(b, a%b, tx, ty);
	x = ty;
	y = tx - (a / b) * ty;
	return g;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	f1[1] = 1, f2[2] = 1;
	rep(i, 3, m) {
		f1[i] = f1[i-1] + f1[i-2];
		f2[i] = f2[i-1] + f2[i-2];
	}
	
	ll k; cin >> k;
	ll ans = 0;
	
	rep(i, 3, m) {
		ll a = f1[i], b = f2[i], x, y;
		ll d = exgcd(a, b, x, y);
		if(k % d) continue;
		if(f1[i] + f2[i] > k) break;
		ll x1 = (x / d * k % (b / d) + (b / d)) % (b / d);
		if(x1 == 0) x1 = b / d;
		ll y1 = (k - a * x1) / b;
		if(y1 < 0) continue;
		ll y2 = (y / d * k % (a / d) + (a / d)) % (a / d);
		if(y2 == 0) y2 = a / d;
		ll x2 = (k - b * y2) / a;
		ans += (x2 - x1) / (b / d) + 1;
	}
	
	cout << ans % P << "\n";
	
	return 0;
}
