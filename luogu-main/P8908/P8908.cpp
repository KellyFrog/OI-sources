// Problem: P8908 [USACO22DEC] Palindromes P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8908
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

const int N = 7.5e3 + 5;

int n;
char s[N];
int cnt1[N], cnt2[N], cnt[N<<1];
vector<int> pos;
ll ans = 0;

void solve(int p1, int p2) {
	memset(cnt, 0, sizeof cnt);
	int l = p1, r = p2;
	int curans = 0;
	int p = n + pos[r] - pos[l], d = n, cntl = 0, cntr = 0;
	while(l > 0 && r+1 < pos.size()) {
		if(l != r) {
			++cnt[pos[r]-pos[l]+d];
			if(pos[r]-pos[l]+d >= p) ++cntr;
			else ++cntl;
			curans += abs(pos[r]-pos[l]+d-p);
		}
		per(i, pos[l-1]+1, pos[l]) {
			int p0 = p, cntl0 = cntl, cntr0 = cntr, curans0 = curans;
			rep(j, pos[r], pos[r+1]-1) {
				if((cnt1[j] - cnt1[i-1] & 1) && (cnt2[j] - cnt2[i-1] & 1)) {
				} else {
					int res = curans0;
					if(p1 == p2) res += abs((i+j >> 1) - pos[p1]);
					ans += res;
				}
				if(p0 >= 0) cntl0 += cnt[p0], cntr0 -= cnt[p0];
				curans0 += cntl0 - cntr0;
				++p0;
			}
			if(p >= 1) {
				curans += cntr - cntl;
				cntl -= cnt[p-1], cntr += cnt[p-1];
			}
			--p;
			d -= 2;
		}
		rep(i, pos[r]+1, pos[r+1]) {
			if(p >= 0) cntl += cnt[p], cntr -= cnt[p];
			curans += cntl - cntr;
			++p;
		}

		--l, ++r;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> (s+1);
	n = strlen(s+1);

	pos.pb(0);
	rep(i, 1, n) {
		if(s[i] == 'G') pos.pb(i);
		cnt1[i] = cnt1[i-1] + (s[i] == 'G');
		cnt2[i] = cnt2[i-1] + (s[i] == 'H');
	}
	pos.pb(n+1);
	rep(l, 1, n) rep(r, l, n) {
		if((cnt1[r] - cnt1[l-1] & 1) && (cnt2[r] - cnt2[l-1] & 1)) ans += -1;
	}
	for(int i = 1; i+1 < pos.size(); ++i) solve(i, i);
	for(int i = 1; i+2 < pos.size(); ++i) solve(i, i+1);

	cout << ans << "\n";
	return 0;
}
