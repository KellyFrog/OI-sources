// Problem: P5468 [NOI2019] 回家路线
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5468
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Create Time: 2022-06-22 19:46:53
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

const int N = 1e6 + 5;

int n, m, a, b, c;
ll f[N];
int p[N<<1];
vector<int> dq[N];
int ql[N], qr[N];
int sx[N], sy[N], st[N], et[N];

inline ll getx(int o) { return et[o]; }
inline ll gety(int o) { return f[o] + 1ll * a * et[o] * et[o] - 1ll * b * et[o]; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> a >> b >> c;
	rep(i, 1, m) cin >> sx[i] >> sy[i] >> st[i] >> et[i], p[i] = i, p[i+m] = -i;
	rep(i, 1, m) ql[i] = 0, qr[i] = 0;
	
	sort(p + 1, p + 2*m + 1, [&](int i, int j) {
		int ti = i < 0 ? et[-i] : st[i];
		int tj = j < 0 ? et[-j] : st[j];
		return ti == tj ? i < j : ti < tj;
	});

	auto push = [&](int id, int i) {
		while(ql[id]+1 < qr[id]) {
			int x = i, y = dq[id][qr[id]-1], z = dq[id][qr[id]-2];
			if((__int128)(gety(y) - gety(z)) * (getx(x) - getx(y)) >= (__int128)(gety(x) - gety(y)) * (getx(y) - getx(z))) {
				// cerr << "poped " << dq[id][qr[id]-1] << "\n";
				--qr[id];
			}
			else break;
		}
		if(qr[id] == dq[id].size()) dq[id].push_back(i);
		else dq[id][qr[id]] = i;
		++qr[id];
	};

	auto query = [&](int id, int i) {
		if(ql[id] == qr[id]) return;
		while(ql[id]+1 < qr[id]) {
			int x = dq[id][ql[id]+1], y = dq[id][ql[id]];
			if((__int128)2 * a * st[i] * (getx(x) - getx(y)) > gety(x) - gety(y)) ++ql[id];
			else break;
		}
		int j = dq[id][ql[id]];
		f[i] = f[j] + 1ll * a * (st[i] - et[j]) * (st[i] - et[j]) + 1ll * b * (st[i] - et[j]) + c;
	};

	memset(f, 0x3f, sizeof f);

	f[0] = 0;
	push(1, 0);

	rep(i, 1, 2*m) {
		if(p[i] < 0) {
			int o = -p[i];
			push(sy[o], o);
		} else {
			int o = p[i];
			query(sx[o], o);
		}
	}
	ll ans = LONG_LONG_MAX;
	rep(i, 1, m) if(sy[i] == n) ans = min(ans, f[i] + et[i]);
	cout << ans << "\n";
	
	return 0;
}