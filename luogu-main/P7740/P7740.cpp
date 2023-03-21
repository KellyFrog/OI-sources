// Problem: P7740 [NOI2021] 机器人游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7740
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Create Time: 2022-05-18 15:58:41
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

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 35;
const int M = 1e3 + 5;
const int S = 1 << 17 | 5;
const int P = 1e9 + 7;

int n, m;
int op[M][N], t[M];
vector<int> adj[N];
bitset<M> f[4][S], all;
bitset<M> g[4][N];
int dp[N][S], pw2[M], pw3[M], ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, m) {
		string str; cin >> str;
		for(char ch : str) {
			if(ch == 'R') ++t[i];
			else if(ch == '0') op[i][t[i]] = 1;
			else if(ch == '1') op[i][t[i]] = 2;
			else if(ch == '*') op[i][t[i]] ^= 3;
		}
		adj[t[i]].pb(i);
	}

	pw2[0] = pw3[0] = 1;
	rep(i, 1, m) {
		pw2[i] = 2ll * pw2[i-1] % P;
		pw3[i] = 3ll * pw3[i-1] % P;
	}

	per(i, 1, n) {
		// cerr << "endpos = " << i << "\n";
		for(int o : adj[n-i]) {
			// cerr << "add = " << o << "\n";
			rep(j, 0, n) {
				// cerr << op[o][j] << " \n"[j == n];
				g[op[o][j]][j][o] = 1;
			}
			all[o] = 1;
		}
		int u1 = (1 << min(i, n - i + 1) + 1) - 1;
		int u2 = (1 << min(i, n - i + 1)) - 1;
		rep(j, 0, min(i, n - i + 1)) {
			rep(k, 0, 3) f[k][1<<j] = g[k][j];
		}
		rep(s, 1, u1) {
			if(__builtin_popcount(s) == 1) continue;
			int s1 = s & (s - 1);
			int s2 = s ^ s1;
			rep(k, 0, 3) f[k][s] = f[k][s1] | f[k][s2];
		}

		dp[0][0] = 1;
		rep(j, 1, i) {
			memset(dp[j], 0, sizeof dp[j]);
			rep(z, 0, 1) rep(s, 0, u2) {
				int p = (z << min(i, n-i+1)) | s;
				int p1 = ((z << min(i, n-i+1)) | (s << 1)) & u1;
				int p2 = ((z << min(i, n-i+1)) | (s << 1 | 1)) & u1;
				if(j != i) dp[j][p1] = (dp[j][p1] + dp[j-1][p]) % P;
				dp[j][p2] = (dp[j][p2] - dp[j-1][p]) % P;
			}
			rep(s, 0, u1) {
				bitset<M> a = (f[1][s] & f[2][s]) | ((j < i ? all : f[0][s]) & f[3][s]);
				bitset<M> b = (f[1][s] | f[2][s]) & ((j < i ? all : f[0][s]) | f[3][s]);
				bitset<M> c = (all ^ a) & (all ^ b); //3
				bitset<M> d = b & (b ^ a); //2
				dp[j][s] = 1ll * dp[j][s] * pw2[d.count()] % P * pw3[c.count()] % P;
				// cerr << "j = " << j << ", s = " << s << " " << a.count() << " " << b.count() << " " << c.count() << " " << d.count() << " " << f[3][s].count() << "\n";
			}
		}

		rep(delt, 1, n-i) {
			// cerr << "delt = " << delt << "\n";
			rep(j, 0, min(i, n - i + 1)) {
				rep(k, 0, 3) f[k][1<<j] = g[k][j+delt];
			}
			rep(s, 1, u1) {
				if(__builtin_popcount(s) == 1) continue;
				int s1 = s & (s - 1);
				int s2 = s ^ s1;
				rep(k, 0, 3) f[k][s] = f[k][s1] | f[k][s2];
			}
			rep(s, 0, u1) {
				bitset<M> a = (f[1][s] & f[2][s]) | (f[0][s] & f[3][s]);
				bitset<M> b = (f[1][s] | f[2][s]) & (f[0][s] | f[3][s]);
				bitset<M> c = (all ^ a) & (all ^ b); //3
				bitset<M> d = b & (b ^ a); //2
				dp[i][s] = 1ll * dp[i][s] * pw2[d.count()] % P * pw3[c.count()] % P;
			}
		}

		rep(s, 0, u1) ans = (ans + dp[i][s]) % P;
		// rep(s, 0, u1) cerr << "i = " << i << ", s = " << s << " " << dp[i][s] << "\n";
	}

	cout << (P - ans) % P << "\n";
	
	return 0;
}