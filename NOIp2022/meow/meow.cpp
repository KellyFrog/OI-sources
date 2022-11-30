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

const int N = 605;
const int M = 2e6 + 5;

int n, m, k;
int a[M], bel[M];
deque<int> dq[N];
vector<pair<int, pair<int, int>>> v;
int pre[M], nxt[M];

inline int getpos() {
	if(nxt[n+2]) return nxt[n+2];
	if(nxt[n+1] && nxt[nxt[n+1]]) return nxt[nxt[n+1]];
	return -1;
}

inline void modify(int id, int rt) {
	assert(1 <= id && id <= n);
	nxt[pre[id]] = nxt[id];
	pre[nxt[id]] = pre[id];
	pre[id] = rt;
	nxt[id] = nxt[rt];
	pre[nxt[rt]] = id;
	nxt[rt] = id;
}

inline void add(int id, int p, bool f) {
	v.emplace_back(1, mp(p, 0));
	int rt = n + dq[p].size() + 1;
	if(!dq[p].empty() && a[dq[p].back()] == a[id]) {
		dq[p].pop_back();
		if(f) bel[a[id]] = 0;
		modify(p, rt - 1);
	} else {
		dq[p].push_back(id);
		if(f) bel[a[id]] = p;
		modify(p, rt + 1);
	}
}

inline void erase(int id, bool f) {
	assert(bel[a[id]]);
	int p = bel[a[id]];
	if(dq[p].size() <=1 || a[dq[p].back()] == a[id]) {
		add(id, p, f);
	} else {
		int pp = nxt[n+1];
		v.emplace_back(1, mp(pp, 0));
		v.emplace_back(2, mp(pp, p));
		int rt = n + dq[p].size() + 1;
		assert(!dq[p].empty());
		dq[p].pop_front();
		if(f) bel[a[id]] = 0;
		modify(p, rt - 1);
	}
}

void solve() {
	v.clear();
	cin >> n >> m >> k;
	rep(i, 1, m) cin >> a[i];

	rep(i, 1, n) pre[i] = i-1, nxt[i] = i+1;
	pre[1] = n+1, nxt[n+1] = 1;
	nxt[n] = nxt[n+2] = nxt[n+3] = 0;

	rep(i, 1, k) bel[i] = 0;
	rep(i, 1, m) {
		if(!bel[a[i]]) {
			int p = getpos();
			if(p == -1) {
				p = nxt[n+1];
				int j = i;
				while(a[j] == a[i] || a[dq[bel[a[j]]].back()] == a[j]) {
					++j;
				}
				int b = bel[a[j]];
				int d = dq[b].back(), e = dq[b].back();
				int c1 = 0, c2 = 1, lst = 0;
				rep(k, i, j) {
					c1 ^= a[k] == a[i];
					c2 ^= a[k] == a[d];
					if(a[k] == a[i]) lst = k;
				}
				rep(k, i, j) {
					if(a[k] != a[i] && a[k] != a[e]) {
						erase(k, 0);
					} else if(a[k] == a[i]) {
						if(!c1 || !c2) {
							add(k, p, 0);
						} else {
							if(k == lst) add(k, b, 0);
							else add(k, p, 0);
						}
					} else {
						add(k, b, 0);
					}
				}
				rep(k, i, j) bel[a[k]] *= -1;
				rep(k, i, j) bel[a[k]] = max(bel[a[k]], 0);
				if(!dq[b].empty() && (a[dq[b].front()] == a[i] || a[dq[b].back()] == a[i])) bel[a[i]] = b;
				if(!dq[p].empty() && (a[dq[p].front()] == a[i] || a[dq[p].back()] == a[i])) bel[a[i]] = p;
				if(!dq[b].empty() && (a[dq[b].front()] == a[d] || a[dq[b].back()] == a[d])) bel[a[d]] = b;
				if(!dq[p].empty() && (a[dq[p].front()] == a[d] || a[dq[p].back()] == a[d])) bel[a[d]] = p;
				i = j;
			} else {
				add(i, p, 1);
			}
		} else {
			erase(i, 1);
		}
	}
	rep(i, 1, n) {
		assert(dq[i].empty());
	}
	cout << v.size() << "\n";
	for(auto e : v) {
		if(e.fi == 1) cout << e.fi << " " << e.se.fi << "\n";
		else cout << e.fi << " " << e.se.fi << " " << e.se.se << "\n";
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
