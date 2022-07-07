// Problem: T249894 距离[2022人大附中特长生T2]
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T249894
// Memory Limit:  MB
// Time Limit:  ms
// Create Time: 2022-07-07 15:50:06
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

const int N =  4e2 + 5;
const int inf = 0x3f3f3f3f;
const int P = 998244353;

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, m, k;
int d[N][N], dis[N][N], w[N][N];
int bel[N], cnt[N];
int fac[N], ifac[N];
int f[N], g[N][N];

inline void dfs(int o) {
	bel[o] = m;
	++cnt[m];
	rep(i, 1, n) if(d[i][o] == 0 && !bel[i]) dfs(i);
}

int solve(int k0) {
	auto calc = [&](int w, int t) {
		return qpow(w, t) - qpow(w-1, t);
	};


	f[0] = 1;
	rep(i, 0, n+1) g[0][i] = 1;
	
	rep(i, 1, n) {
		f[i] = qpow(k0+1, i * (i-1) / 2);
		rep(j, 1, n+1) g[i][j] = 0;
		per(j, 1, i-1) per(k, 1, i) {
			if(j * k > i) continue;
			int t = 1ll * fac[i] * qpow(ifac[j], k) % P * ifac[k] % P * ifac[i-j*k] % P * (k ? qpow(k0, j*k*(i-j*k) + k*(k-1)/2*j*j) : 1) % P * qpow(f[j], k) % P * g[i-j*k][j+1] % P;
    		g[i][j] = (g[i][j] + t) % P;
		}
        per(j, 1, i-1) g[i][j] = (g[i][j] + g[i][j+1]) % P;
		f[i] = (f[i] - g[i][1]) % P;
		rep(j, 1, i) g[i][j] = (g[i][j] + f[i]) % P;
	}


	int ans = 1;

	rep(i, 1, m) ans = 1ll * ans * f[cnt[i]] % P;
	
	rep(i, 1, m) rep(j, 1, m) {
		if(i >= j) continue;
		if(w[i][j] == -2) {
            if(dis[i][j] > k0) return 0;
			ans = 1ll * ans * calc(k0 - dis[i][j] + 1, cnt[i] * cnt[j]) % P;
		} else {
			rep(k, 1, n) {
				if(i != k && j != k) continue;
				w[i][j] = max(w[i][j], dis[i][k] - dis[j][k]);
				w[i][j] = max(w[i][j], dis[j][k] - dis[i][k]);
			}

            if(w[i][j] > k0) return 0;

			ans = 1ll * ans * qpow(k0 - w[i][j] + 1, cnt[i] * cnt[j]) % P;
		}
	}

	return ans;

}

void solve() {
	cin >> n >> k;
	rep(i, 1, n) rep(j, 1, n) w[i][j] = -1;
	rep(i, 1, n) rep(j, 1, n) cin >> d[i][j];
	rep(i, 1, n) bel[i] = 0, cnt[i] = 0;
	m = 0;
	rep(i, 1, n) {
		if(bel[i]) continue;
		++m;
		dfs(i);
	}

	rep(i, 1, m) rep(j, 1, m) dis[i][j] = inf;
	rep(i, 1, n) rep(j, 1, n) {
		dis[bel[i]][bel[j]] = min(dis[bel[i]][bel[j]], d[i][j]);
	}

    rep(i, 1, n) rep(j, 1, n) if(dis[bel[i]][bel[j]] != d[i][j]) {
        cout << 0 << "\n";
        return;
    }

	rep(i, 1, m) rep(j, 1, m) {
		if(i == j) continue;
		bool ok = 0;
        int mi = inf;
        rep(k, 1, m) if(k != i && k != j) mi = min(mi, dis[i][k] + dis[k][j]);
        if(mi < dis[i][j]) {
            cout << 0 << "\n";
            return;
        }
		rep(k, 1, n) if(k != i && k != j && dis[i][j] == dis[i][k] + dis[k][j]) ok = 1;
		if(!ok) w[i][j] = -2;
	}

	int ans1 = solve(k), ans2 = solve(k-1);

	cerr << "ans = " << ans1 << " " << ans2 << "\n";

	int ans = (ans1 - ans2) % P;
	cout << (ans + P) % P << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int n = 400;
	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % P;
	ifac[n] = qpow(fac[n], P - 2);
	per(i, 2, n-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}