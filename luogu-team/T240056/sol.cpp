// Problem: T240056 [PKUSC2021 D1T2] 逛街
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T240056
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Create Time: 2023-05-01 20:11:13
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

const int N = 3e5 + 5;

mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

//mt19937 mtrnd(0x1145);

int n, q;
int a[N], b[N], c[N];
vector<int> adj[N];
ll t[N];
int dfn[N], siz[N], dfncnt, pos[N], fat[N], cnt[N];
int st[20][N], lg2[N];
bool vis[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, ll val) { for(int x0 = x; x0 <= n+1; x0 += lowbit(x0)) t[x0] += val; }
inline void add(int l, int r, ll val) { add(l, val), add(r+1, -val); }
inline ll query(int x) { ll ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }

inline int querymx(int l, int r) {
	int j = lg2[r-l+1];
	return max(st[j][l], st[j][r-(1<<j)+1]);
}

struct fhq {
	unsigned pri[N];
	int ls[N], rs[N], val[N], siz[N], tt, rt;

	fhq() : tt(0), rt(0) {}

	inline int newnode(int v) {
		int o = ++tt;
		ls[o] = rs[o] = 0;
		val[o] = v, siz[o] = 1;
		pri[o] = mtrnd();
		return o;
	}

	inline void pushup(int o) {
		siz[o] = siz[ls[o]] + siz[rs[o]] + 1;
	}

	inline void split(int o, int& o1, int& o2, int k) {
		if(!o) {
			o1 = o2 = 0;
			return;
		}
		if(k <= siz[ls[o]]) {
			o2 = o;
			split(ls[o], o1, ls[o2], k);
			pushup(o2);
		} else {
			o1 = o;
			split(rs[o], rs[o1], o2, k-siz[ls[o]]-1);
			pushup(o1);
		}
	}

	inline void merge(int& o, int o1, int o2) {
		if(!o1 || !o2) {
			o = o1 + o2;
			return;
		}
		if(pri[o1] < pri[o2]) {
			o = o1;
			merge(rs[o], rs[o1], o2);
		} else {
			o = o2;
			merge(ls[o], o1, ls[o2]);
		}
		pushup(o);
	}

	inline void dfs(int o) {
		if(!o) return;
		dfs(ls[o]);
		cerr << val[o] << " ";
		dfs(rs[o]);
	}

} tr1, tr2;
int rt1, rt2;

inline void dfs(int u) {
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	for(int v : adj[u]) dfs(v), siz[u] += siz[v];
	add(dfn[u], dfn[u] + siz[u] - 1, b[a[u]]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) c[i] = b[i] = a[i];
	sort(b + 1, b + n + 1);
	int m = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	rep(i, 1, n) b[i] = c[i];
	sort(b + 1, b + n + 1);
	rep(i, 1, n) ++cnt[a[i]];
	rep(i, 1, m) cnt[i] += cnt[i-1];
	rep(i, 1, n) a[i] = cnt[a[i]]--;
	rep(i, 1, n) pos[a[i]] =i ;

	lg2[0] = -1;
	rep(i, 1, n) lg2[i] = lg2[i>>1] + 1;
	rep(i, 1, n) st[0][i] = a[i];
	rep(j, 1, 19) rep(i, 1, n) {
		if(i + (1 << j) - 1 > n) break;
		st[j][i] = max(st[j-1][i], st[j-1][i+(1<<j-1)]);
	}

	a[n+1] = n+1;
	stack<int> s;
	s.emplace(n+1);
	per(i, 1, n) {
		while(a[i] > a[s.top()]) s.pop();
		fat[i] = s.top();
		adj[s.top()].pb(i);
		s.emplace(i);
	}
	dfs(n+1);

	rep(i, 1, n) {
		int x = tr1.newnode(i);
		int y = tr2.newnode(a[i]);
		tr1.merge(rt1, rt1, x);
		tr2.merge(rt2, rt2, y);
	}
	
	assert(tr1.siz[rt1] == n);
	assert(tr2.siz[rt2] == n);


	while(q--) {
		int op, l, r; cin >> op >> l >> r;
		if(op == 1) {
			if(l == r) continue;
			int a, b, c, d, e, f, g, h, i, j;
			tr1.split(rt1, a, b, l-1);
			tr1.split(b, b, c, r-l+1);
			tr2.split(rt2, d, e, l-1);
			tr2.split(e, e, f, r-l+1);

			//a [g b h] c
			tr1.split(b, g, b, 1);
			tr1.split(b, b, h, r-l-1);
			tr1.val[g] = tr1.val[h];
			tr1.merge(rt1, a, b);
			tr1.merge(rt1, rt1, g);
			tr1.merge(rt1, rt1, h);
			tr1.merge(rt1, rt1, c);

			//d [i j e] f
			tr2.split(e, i, e, 1);
			tr2.split(e, j, e, 1);
			int v = min(tr2.val[i], tr2.val[j]);
			if(v) {
				int u = pos[v];
				add(dfn[u], dfn[u] + siz[u] - 1, -::b[::a[u]]);
				vis[v] = 1;
			}
			tr2.val[i] = max(tr2.val[i], tr2.val[j]);
			tr2.val[j] = 0;
			tr2.merge(rt2, d, i);
			tr2.merge(rt2, rt2, e);
			tr2.merge(rt2, rt2, j);
			tr2.merge(rt2, rt2, f);
		} else {
			int x, y;
			if(r - l + 1 > 1) {
				int a, b, c, d, e;
				tr1.split(rt1, a, b, l-1);
				tr1.split(b, b, c, r-l+1);
				tr1.split(b, d, b, 1);
				tr1.split(b, b, e, r-l-1);
				x = querymx(l, tr1.val[d]);
				y = querymx(l, tr1.val[e]);
				tr1.merge(rt1, a, d);
				tr1.merge(rt1, rt1, b);
				tr1.merge(rt1, rt1, e);
				tr1.merge(rt1, rt1, c);
			} else {
				int a, b, c;
				tr1.split(rt1, a, b, l-1);
				tr1.split(b, b, c, r-l+1);
				x = y = querymx(l, tr1.val[b]);
				tr1.merge(rt1, a, b);
				tr1.merge(rt1, rt1, c);
			}
			ll ans = query(dfn[pos[x]]) - query(dfn[fat[pos[y]]]);
			if(vis[x]) ans += b[x];
			cout << ans << "\n";
		}
		assert(tr1.siz[rt1] == n);
		assert(tr2.siz[rt2] == n);
	}
	
	return 0;
}

