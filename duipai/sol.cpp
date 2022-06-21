// Problem: P5469 [NOI2019] 机器人
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5469
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// Create Time: 2022-06-21 13:56:12
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

const int N = 3e2 + 15;
const int P = 1e9 + 7;

int qpow(int x, int p) {
	int res = 1, base = x ;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base= 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, k;
int a[N], b[N], nd[N<<1];
int val[N][N][N], vis[N][N];
int ifac[N], pre[N], suf[N];
int t, vl, vr, len;
vector<pair<int, int>> range;

inline void init(int l, int r) {
	if(l > r) return;
	int mid = l + r >> 1;
	rep(i, mid - 1, mid + 1) {
		if(i < l || i > r) continue;
		if(abs(r+1-i - (i-(l-1))) > 2) continue;
		if(l != r) {
			init(l, i - 1);
			init(i + 1, r);
		}
	}
	range.emplace_back(l, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;

	k = n + 10;
	int fac = 1;
	rep(i, 2, k) fac = 1ll * fac * i % P;
	ifac[k] = qpow(fac, P - 2);
	per(i, 0, k-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;

	rep(i, 1, n) cin >> a[i] >> b[i], nd[2*i-1] = a[i]-1, nd[2*i] = b[i];
	sort(nd + 1, nd + 2*n + 1);

	init(1, n);

	cerr << range.size() << "\n";

	rep(i, 1, 2*n) {
		vl = nd[i-1] + 1, vr = nd[i];
		len = min(vr - vl + 1, k);
		t = i;
		
		if(vl > vr) continue;

		for(auto [l, r] : range) {
			int mid = l + r >> 1;
			rep(k, 1, len) val[l][r][k] = 0;
			val[l][r][0] = val[l][r][k+1];

			rep(i, mid - 1, mid + 1) {
				if(i < l || i > r) continue;
				if(abs(r+1-i - (i-(l-1))) > 2) continue;
				rep(k, 1, len) {
					val[l][r][k] = (val[l][r][k] + 1ll * (a[i] <= vl && vr <= b[i]) * (i-1 < l ? 1 : val[l][i-1][k]) * (i+1 > r ? 1 : val[i+1][r][k-1])) % P;
				}
			}

			rep(k, 1, len) val[l][r][k] = (val[l][r][k-1] + val[l][r][k]) % P;

			
			if(len == vr - vl + 1) { 
				val[l][r][k+1] = val[l][r][len];
				continue;
			}

			int px = vr - vl + 1;

			pre[0] = suf[k+1] = 1;
			rep(i, 1, k) pre[i] = 1ll * pre[i-1] * (px - i) % P;
			per(i, 1, k) suf[i] = 1ll * suf[i+1] * (px - i) % P;
			int ans = 0;
			rep(i, 1, k) {
				ans = (ans + (k - i & 1 ? -1ll : 1ll) * pre[i-1] * suf[i+1] % P * ifac[i-1] % P * ifac[k-i] % P * val[l][r][i]) % P;
			}
			val[l][r][k+1] = ans;
		}
	}
	
	cout << (val[1][n][k+1] + P) % P << "\n";
	
	return 0;
}