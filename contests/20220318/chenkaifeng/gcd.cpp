#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e6 + 5;

vector<int> pfac[N];
int n, q;
set<int> pos[N], pre[N];
bool vis[N];
int val[N];
int mx[N<<2];

inline void modify(int o, int p, int val, int l, int r) {
    if(l == r) {
	mx[o] = val;
	return;
    }
    int mid = l + r >> 1;
    if(p <= mid) modify(o << 1, p, val, l, mid);
    else modify(o << 1 | 1, p, val, mid + 1, r);
    mx[o] = max(mx[o<<1], mx[o<<1|1]);
}

inline int query(int o, int ql, int qr, int l, int r) {
    if(ql <= l && r <= qr) return mx[o];
    int mid = l + r >> 1;
    int res = 0;
    if(ql <= mid) res = max(res, query(o << 1, ql, qr, l, mid));
    if(mid < qr) res = max(res, query(o << 1 | 1, ql, qr, mid + 1, r));
    return res;
}

inline void update(int x) {
    if(x == 0 || x == n+1) return;
    val[x] = pre[x].empty() ? 0 : *pre[x].rbegin();
    //cerr << "update " << x << " to " << val[x] << "\n";
    modify(1, x, val[x], 1, n);
}

int main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> q;
    rep(i, 2, n) {
	if(pfac[i].empty()) {
	    for(int j = i; j <= n; j += i) {
		pfac[j].pb(i);
	    }
	    pos[i].insert(0);
	    pos[i].insert(n+1);
	}
    }

    while(q--) {
	char op;
	cin >> op;
	if(op == 'S') {
	    int x; cin >> x;
	    if(vis[x]) {
		for(int p : pfac[x]) {
		    auto it = pos[p].find(x);
		    auto mid = it;
		    auto last = mid, nxt = mid;
		    --last, ++nxt;
		    pre[*nxt].erase(x);
		    pre[*nxt].insert(*last);
		    update(*nxt);
		    pos[p].erase(x);
		}
		pre[x].clear();
		update(x);
		vis[x] = 0;
	    } else {
		//cerr << "x = " << x << "\n";
		for(int p : pfac[x]) {
		    auto mid = pos[p].lower_bound(x);
		    //cerr << "fac = " << p << " get pos = " << *mid << "\n";
		    auto last = mid, nxt = mid;
		    --last;
		    pre[*nxt].erase(*last);
		    pre[*nxt].insert(x);
		    pre[x].insert(*last);
		    update(*nxt);
		    pos[p].insert(x);
		}
		update(x);
		vis[x] = 1;
	    }
	} else {
	    int l, r;
	    cin >> l >> r;
	    int v = query(1, l, r, 1, n);
	    cout << (v >= l ? "yes" : "no") << "\n";
	}
    }

    cout.flush();
    
    return 0;
}
