// Problem: P8407 [COCI2021-2022#6]  Superpozicija
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8407
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-08-17 16:26:55
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

const int N = 2e5 + 5;

int n;
int a[N], b[N];
int c[N], d[N], p[N], ans[N];
char s[N];

void solve() {
	cin >> n;
	cin >> s+1;
	rep(i, 1, 2*n) c[i] = d[i] = p[i] = 0;
	rep(i, 1, n) ans[i] = -1;
	rep(i, 1, n) {
		cin >> a[i] >> b[i];
		if(s[a[i]] == s[b[i]]) {
			if(s[a[i]] == '(') ++c[a[i]], ans[i] = 0;
			else --c[b[i]], ans[i] = 1;
		} else {
			if(s[a[i]] == '(') {
				--c[b[i]];
				ans[i] = 1;
			} else {
				--c[a[i]];
				ans[i] = 0;
			}
			if(a[i] > b[i]) swap(a[i], b[i]);
			p[a[i]] = i;
		}
	}
	rep(i, 1, 2*n) c[i] += c[i-1];
	if(c[2*n] > 0) {
		cout << -1 << "\n";
		return;
	}
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	rep(i, 1, 2*n) {
		if(p[i]) {
			pq.emplace(b[p[i]], p[i]);
		}
		d[i] += d[i-1];
		int t = -(d[i] + c[i]);
		if(t < 0) continue;
		while(t--) {
			if(pq.empty()) {
				cout << -1 << "\n";
				return;
			}
			auto [r, j] = pq.top(); pq.pop();
			++d[i], ++d[max(i,r)];
			ans[j] ^= 1;
		}
	}
	if(d[2*n] + c[2*n] != 0) {
		cout << -1 << "\n";
		return;
	}
	rep(i, 1, n) cout << ans[i] << " \n"[i == n];
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
