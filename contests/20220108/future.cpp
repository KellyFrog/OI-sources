/*
 * Author: chenkaifeng @BDFZ
 */
 
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

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

// const int mod = 1e9 + 7;
const int mod = 998244353;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		p >>= 1;
	}
	return res;
}

template<typename T> inline void upd(T& x, const T& y) {	x += y;	if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 5e3 + 6;

int son[N][26], fail[N],cnt[N], rt=1, tot=1, que[N], ph=1, pt=0;
char s[N], t[N];
int n, m;
ll f[2][N], g[2][N];

void insert() {
	int cur = rt;
	int len = strlen(s+1);
	rep(i, 1, len) {
		if(!son[cur][s[i]-'a']) son[cur][s[i]-'a'] = ++tot;
		cur = son[cur][s[i]-'a'];
	}
	++cnt[cur];
}

void buildfail() {
	rep(i, 0, 25) {
		if(son[rt][i]) fail[son[rt][i]] = rt, que[++pt] = son[rt][i];
		else son[rt][i] = rt;
	}
	while(ph <= pt) {
		int cur = que[ph++];
		rep(i, 0, 25) {
			if(son[cur][i]) fail[son[cur][i]] = son[fail[cur]][i], que[++pt] = son[cur][i];
			else son[cur][i] = son[fail[cur]][i];
		}
	}
	rep(i, 1, tot) cnt[que[i]] += cnt[fail[que[i]]];
}

int main() {
	freopen("future.in", "r", stdin);
	freopen("future.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	clock_t st = clock();
	
	cin >> (t+1);
	n = strlen(t+1);
	cin >> m;
	rep(i, 1, m) {
		cin >> (s+1);
		insert();
	}
	buildfail();
	
	f[0][rt] = 1, g[0][rt] = 0;
	
	int inv = qpow(26, mod-2);
	
	rep(i, 1, n) {
		memset(f[i&1], 0, sizeof f[i&1]);
		memset(g[i&1], 0, sizeof g[i&1]);
		// cerr << "i=" << i << "\n";
		rep(j, 1, tot) {
			if(t[i] == '?') {
				rep(k, 0, 25) {
					int t = son[j][k];
					f[i&1][t] += f[i-1&1][j];
					g[i&1][t] += g[i-1&1][j];
				}
			} else {
				int tt = son[j][t[i]-'a'];
				f[i&1][tt] += f[i-1&1][j];
				g[i&1][tt] += g[i-1&1][j];
			}
		}
		rep(j, 1, tot) {
			if(f[i&1][j]) f[i&1][j] %= mod;
			if(g[i&1][j]) g[i&1][j] %= mod;
		}
		if(t[i] == '?') {
			rep(j, 1, tot) {
				if(f[i&1][j]) f[i&1][j] = f[i&1][j]*inv%mod;
				if(g[i&1][j]) g[i&1][j] = g[i&1][j]*inv%mod;
			}
		}
		rep(j, 1, tot) g[i&1][j] = (1ll*f[i&1][j]*cnt[j]+g[i&1][j])%mod;
		// rep(j, 1, tot) cerr << f[i&1][j] << " \n"[j == tot];
		// rep(j, 1, tot) cerr << g[i&1][j] << " \n"[j == tot];
	}
	
	ll ans = 0;
	rep(i, 1, tot) ans += g[n&1][i];
	cout << ans%mod << "\n";
	
	clock_t tt = clock();
	
	cerr << (float)(tt - st) / CLOCKS_PER_SEC << "\n";
	
	return 0;
}
