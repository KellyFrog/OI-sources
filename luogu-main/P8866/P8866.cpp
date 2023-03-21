// Problem: P8866 [NOIP2022] 喵了个喵
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8866
// Memory Limit: 512 MB
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

const int N = 2e6 + 5;
const int M = 305;

int n, m, k, a[N];
int b[M][2], sz[M], pos[N];
vector<tuple<int, int, int>> ans;
set<int> s[4];

void update(int p) {
	s[0].erase(p), s[1].erase(p);
	if(b[p][0] == 0) s[0].insert(p);
	else if(b[p][1] == 0) s[1].insert(p);
}

int getpos(int d) {
	if(s[d].empty()) return -1;
	return *s[d].begin();
}

void erase(int x) {
	assert(pos[x] != 0);
	int ep = getpos(0);
	assert(b[ep][0] == 0);
	if(b[pos[x]][0] == x) {
		ans.emplace_back(1, ep, 0);
		ans.emplace_back(2, ep, pos[x]);
		b[pos[x]][0] = b[pos[x]][1];
		b[pos[x]][1] = 0;
	} else {
		ans.emplace_back(1, pos[x], 0);
		b[pos[x]][1] = 0;
	}
	update(pos[x]);
	pos[x] = 0;
}

void ins(int x, int p) {
	//cerr << "ins(" << x << "," << p << ")\n";
	ans.emplace_back(1, p, 0);
	if(b[p][1] == x) {
		b[p][1] = 0;
	} else if(b[p][1] == 0 && b[p][0] == x) {
		b[p][0] = 0;
	} else {
		assert(b[p][1] == 0);
		if(b[p][0]) b[p][1] = x;
		else b[p][0] = x;
	}
	update(p);
}

void solve() {
	cin >> m >> n >> k;
	//cerr << "solve=" << n << " " << m << " " << k << "\n";
	rep(i, 1, n) cin >> a[i];
	ans.clear();
	s[0].clear(), s[1].clear(), s[2].clear();
	rep(i, 1, m) {
		b[i][0] = b[i][1] = 0;
		s[0].insert(i);
	}
	rep(i, 1, k) pos[i] = 0;
	int c = 0;
	rep(i, 1, n) {
		//cerr << "i=" << i << " " << a[i] << "\n";
		if(pos[a[i]]) {
			//cerr << "erase = " << a[i]  << "\n";
			erase(a[i]);
		} else {
			if(s[0].size() + s[1].size() > 1) {
				int p = -1;
				if(!s[1].empty()) p = *s[1].begin();
				else p = *s[0].begin();
				ins(a[i], p);
				pos[a[i]] = p;
			} else {
				int j = i+1;
				int p = getpos(0);
				while(a[j] != a[i] && b[pos[a[j]]][0] != a[j]) ++j;
				if(a[j] == a[i]) {
					ins(a[i], p);
					pos[a[i]] = p;
					rep(k, i+1, j) ins(a[k], pos[a[k]]);
					rep(k, i, j) pos[a[k]] = (b[pos[a[k]]][0] == a[k] || b[pos[a[k]]][1] == a[k]) ? pos[a[k]] : 0;
				} else {
					int c = b[pos[a[j]]][1];
					int s = 0;
					rep(k, i+1, j) s += a[k] == c;
					if(s & 1) {
						ins(a[i], p);
						pos[a[i]] = p;
						rep(k, i+1, j) ins(a[k], pos[a[k]]);
						rep(k, i, j) pos[a[k]] = (b[pos[a[k]]][0] == a[k] || b[pos[a[k]]][1] == a[k]) ? pos[a[k]] : 0;
					} else {
						ans.emplace_back(1, pos[a[j]], 0);
						rep(k, i+1, j-1) {
							if(a[k] == c) ans.emplace_back(1, p, 0);
							else ins(a[k], pos[a[k]]);
						}
						ans.emplace_back(1, p, 0);
						ans.emplace_back(2, pos[a[j]], p);
						b[pos[a[j]]][0] = c, b[pos[a[j]]][1] = a[i];
						pos[a[i]] = pos[a[j]];
						rep(k, i, j) pos[a[k]] = (b[pos[a[k]]][0] == a[k] || b[pos[a[k]]][1] == a[k]) ? pos[a[k]] : 0;
						rep(k, i, j) if(pos[a[k]]) update(pos[a[k]]);
					}
				}
				i = j;
			}
		}
	}
	cout << ans.size() << "\n";
	for(auto [x, y, z] : ans) {
		if(x == 1) cout << 1 << " " << y << "\n";
		else cout << 2 << " " << y << " " << z << "\n";
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	//cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}
