// Problem: CF1043F Make It One
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1043F
// Memory Limit: 250 MB
// Time Limit: 3000 ms
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

const int N = 3e5 + 5;

int n, m = 3e5;
int cnt1[N], cnt2[N], s1[N], s2[N];
ll s[N];
vector<int> prm;
bool vis[N];

void solve() {
	memcpy(s1, cnt1, sizeof s1);
	memcpy(s2, cnt2, sizeof s2);
	
	for(int p : prm) {
		for(int i = m / p * p; i; i -= p) {
			int x = i / p;
			s1[x] += s1[i];
			s2[x] += s2[i];
		}
	}
	per(i, 1, m) {
		s[i] = 1ll * s1[i] * s2[i];
		for(int j = i + i; j <= m; j += i) s[i] -= s[j];
	}
	rep(i, 1, m) cnt2[i] = !!s[i];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	int g = 0;
	rep(i, 1, n) {
		int x; cin >> x;
		g = g ? __gcd(g, x) : x;
		cnt1[x] = 1;
	}
	memcpy(cnt2, cnt1, sizeof cnt2);
	
	if(g != 1) {
		cout << -1 << "\n";
		return 0;
	}
	
	rep(i, 2, m) if(!vis[i]) {
		prm.pb(i);
		for(int j = i + i; j <= m; j += i) vis[j] = 1;
	}
	
	int ans = 1;
	for(; !cnt2[1]; ++ans) solve();
	cout << ans << "\n";
	
	return 0;
}
