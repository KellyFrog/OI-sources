// Problem: #6741. 因子统计
// Contest: LibreOJ
// URL: https://loj.ac/p/6741
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

const int N = 1e6 + 5;
const int M = 1e3 + 5;
const int P = 1e9 + 7;

int n = 1e6, q;
int qx[N], qy[N], a[N], b[N], ans[N];
bool vis[N];

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> q;
	rep(i, 1, q) cin >> qx[i] >> qy[i], ans[i] = 1;

	rep(i, 2, n) {
		if(!vis[i]) {
			for(int j = i; j <= n; j += i) vis[j] = 1;
			if(i <= 1000) {
				memset(a, 0, sizeof a);
				for(int j = i; j <= n; j += i) a[j] = a[j/i] + 1, vis[j] = 1;
				rep(j, 1, n) a[j] += a[j-1];
				rep(j, 1, q) ans[j] = 1ll * ans[j] * (a[qx[j]] - a[qy[j]] - a[qx[j]-qy[j]] + 1) % P;
			} else {
				for(int j = i; j <= n; j += i) ++b[j];
			}
		}
	}
	rep(i, 1, n) b[i] += b[i-1];
	rep(i, 1, q) {
		ans[i] = 1ll * ans[i] * qpow(2, b[qx[i]] - b[qy[i]] - b[qx[i]-qy[i]]) % P;
	}
	rep(i, 1, q) cout << ans[i] << "\n";
		

	return 0;
}
