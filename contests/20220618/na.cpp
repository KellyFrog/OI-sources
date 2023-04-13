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

void solve() {
	// cerr << "---" << "\n";
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(n);
	for(int& x : a) cin >> x;
	for(int& x : b) cin >> x;
	queue<vector<int>> q;
	map<vector<int>, int> dis;

	q.push(a);
	dis[a] = 0;
	int cnt = 0;

	while(!q.empty()) {
		auto e = q.front(); q.pop();
		int d = dis[e];
		++cnt;
		for(int i = 0; i < n - m; ++i) {
			auto v = e;
			int x = v[i+m];
			for(int j = i + m; j > i; --j) v[j] = v[j-1];
			v[i] = x;

			if(!dis.count(v)) {
				dis[v] = d + 1;
				q.push(v);
			}
		}
		for(int i = 0; i < n - m; ++i) {
			auto v = e;
			int x = v[i];
			for(int j = i; j < i + m; ++j) v[j] = v[j+1];
			v[i+m] = x;
			if(!dis.count(v)) {
				dis[v] = d + 1;
				q.push(v);
			}
		}
	}

	if(dis.count(b)) {
		cout << "YES" << "\n";
		// cout << dis[b] << "\n";
		assert(dis[b] <= n * n * n);
	} else {
		cout << "NO" << "\n";
	}
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