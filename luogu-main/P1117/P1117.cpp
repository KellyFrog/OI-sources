// Problem: P1117 [NOI2016] 优秀的拆分
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1117
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// Create Time: 2022-07-04 10:19:23
// Author: Chen Kaifeng
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

const int N = 6e4 + 5;

int n;
char s[N], ss[N];
int rk[N<<1], sa[N], oldrk[N<<1], cnt[N], tmp[N], h[N];
int st[20][N], lg2[N];
int ans1[N], ans2[N];

inline bool iseq(int i, int j, int w) {
	return oldrk[i] == oldrk[j] && oldrk[i+w] == oldrk[j+w];
}

void buildsa() {
	rep(i, 1, 2*n+1) rk[i] = ss[i];
	int p = 300;
	for(int w = 1; w <= 2*n+1; w <<= 1) {
		rep(i, 0, p) cnt[i] = 0;
		rep(i, 1, 2*n+1) ++cnt[rk[i+w]];
		rep(i, 1, p) cnt[i] += cnt[i-1];
		per(i, 1, 2*n+1) tmp[cnt[rk[i+w]]--] = i;
		rep(i, 0, p) cnt[i] = 0;
		rep(i, 1, 2*n+1) ++cnt[rk[i]];
		rep(i, 1, p) cnt[i] += cnt[i-1];
		per(i, 1, 2*n+1) sa[cnt[rk[tmp[i]]]--] = tmp[i];
		memcpy(oldrk, rk, sizeof rk);
		p = 0;
		rep(i, 1, 2*n+1) {
			if(!iseq(sa[i], sa[i-1], w)) ++p;
			rk[sa[i]] = p;
		}
		if(p == 2*n+1) break;
	}
}

void buildh() {
	int p = 0;
	rep(i, 1, 2*n+1) {
		if(p) --p;
		while(i+p <= 2*n+1 && sa[rk[i]-1]+p <= 2*n+1 && ss[i+p] == ss[sa[rk[i]-1]+p]) ++p;
		h[rk[i]] = p;
	}
}

void buildst() {
	lg2[0] = -1;
	rep(i, 1, 2*n+1) lg2[i] = lg2[i>>1] + 1;
	rep(i, 1, 2*n+1) st[0][i] = h[i];
	rep(j, 1, 19) rep(i, 1, 2*n+1) {
		if(i + (1<<j) - 1 > 2*n+1) break;
		st[j][i] = min(st[j-1][i], st[j-1][i+(1<<j>>1)]);
	}
}

inline int lcp(int i, int j) {
	i = rk[i], j = rk[j];
	if(i > j) swap(i, j);
	++i;
	int k = lg2[j-i+1];
	return min(st[k][i], st[k][j-(1<<k)+1]);
}

void solve() {
	cin >> (s+1);
	n = strlen(s+1);
	rep(i, 1, n) ss[i] = s[i];
	ss[n+1] = '#';
	rep(i, 1, n) ss[i+n+1] = s[n-i+1];
	rep(i, 1, 4*n+2) rk[i] = sa[i] = 0;
	buildsa();
	buildh();
	buildst();
	rep(i, 1, n+1) ans1[i] = ans2[i] = 0;
	rep(len, 1, n) {
		for(int i = len; i+len <= n; i += len) {
			int x = lcp(n-i+1 + n+1, n-(i+len)+1 + n+1);
			int y = lcp(i, i+len);
			int l = max(i-len+1, i-x+1);
			int r = min(i, i-len+y);
			if(l > r) continue;
			
			++ans2[l], --ans2[r+1];

			int l1 = l+2*len-1;
			int r1 = min(n, r+2*len-1);

			if(l1 <= r1) {
				++ans1[l1], --ans1[r1+1];
			}
		}
	}
	rep(i, 1, n) ans1[i] += ans1[i-1], ans2[i] += ans2[i-1];
	ll ans = 0;
	rep(i, 1, n) ans += 1ll * ans1[i] * ans2[i+1];
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}