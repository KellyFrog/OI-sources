// Problem: P7413 [USACO21FEB] Stone Game G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7413
// Memory Limit: 250 MB
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

const int N = 1e6 + 5;

int n, a[N], cnt[N], pre[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i], ++cnt[a[i]];
	int m = 1e6;
	rep(i, 1, m) pre[i] = pre[i-1] + cnt[i];
	ll ans = 0;
	rep(i, 1, m) {
		auto getsum = [&](int l, int r) { return pre[min(r, m)] - pre[l-1]; };
		int cnt = 0;
		for(int j = i; j <= m; j += i) cnt += (getsum(j, i+j-1) & 1);
		if(cnt == 0 || cnt > 2) continue;
		if(cnt == 1) {
			if(getsum(i, 2*i-1) & 1) ans += getsum(i, 2*i-1);
		} else {
			for(int j = i; j <= m; j += i) {
				if((getsum(j, i+j-1) & 1) && (getsum(j-i, j-1) & 1)) ans += getsum(j, i+j-1);
			}
		}
	}
	cout << ans << "\n";
	
	return 0;
}
