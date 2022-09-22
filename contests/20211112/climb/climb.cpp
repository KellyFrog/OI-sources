/*
 * Author: chenkaifeng @BDFZ
 */
 
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

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;
const int mod = 998244353;

int qpow(int x, ll p) {
    int res = 1, base = x;
    while(p) {
	if(p & 1) res = 1ll * res * base % mod;
	base = 1ll * base * base % mod;
	p >>= 1;
    }
    return res;
}

inline void upd(int& x, int y) {
    x += y;
    if(x >= mod) x -= mod;
}

inline void upd(int& x, int y, int z) {
    x = y + z;
    if(x >= mod) x -= mod;
}

int mul[N<<2], add[N<<2], sum[N<<2], fval[N<<2], cnt[N<<2];
int dfn[N], dfncnt, siz[N], dep[N], dis[N], val[N], valf[N];
vector<int> adj[N];
int n, q;
int fat[N], f[N], w[N], a[N], psum[N], isum[N];
int pre[N];
int lcnt = 0;

inline void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    upd(dis[u], dis[fa], a[u]);
    dfn[u] = ++dfncnt;
    siz[u] = 1;
    bool leaf = 1;
    psum[u] = 0;
    for(int v : adj[u]) {
	if(v != fa) {
	    leaf = 0;
	    upd(psum[u], w[v]);
	}
    }

    valf[dfn[u]] = f[u];
    
    if(leaf) {
	val[dfn[u]] = 1ll * f[u] * dis[u] % mod;
	++lcnt;
	return;
    }

    isum[u] = qpow(psum[u], mod-2);
    for(int v : adj[u]) {
	if(v != fa) {
	    f[v] = 1ll * f[u] * w[v] % mod * isum[u] % mod;
	    dfs(v, u);
	    siz[u] += siz[v];
	}
    }
}

inline void setmul(int cur, int x) {
    if(x == 1) return;
    mul[cur] = 1ll * mul[cur] * x % mod;
    add[cur] = 1ll * add[cur] * x % mod;
    sum[cur] = 1ll * sum[cur] * x % mod;
    fval[cur] = 1ll * fval[cur] * x % mod;
    cerr << "node " << cur << " " << x << " " << sum[cur] << "\n";
}

inline void pushdown(int cur, int l, int r) {
    int mid = l + r >> 1;
    setmul(cur<<1, mul[cur]);
    setmul(cur<<1|1, mul[cur]);
    mul[cur] = 1, add[cur] = 0;
}

inline void pushup(int cur) {
    upd(sum[cur], sum[cur<<1], sum[cur<<1|1]);
    upd(fval[cur], fval[cur<<1], fval[cur<<1|1]);
}

inline void build(int cur, int l, int r) {
    mul[cur] = 1;
    sum[cur] = 0;
    if(l == r) {
	sum[cur] = val[l];
	if(val[l]) fval[cur] = valf[l];
	return;
    }
    int mid = l + r >> 1;
    build(cur << 1, l, mid);
    build(cur << 1 | 1, mid + 1, r);
    pushup(cur);
    upd(cnt[cur], cnt[cur<<1], cnt[cur<<1|1]);
}

inline void modify(int cur, int ql, int qr, int op, int x, int l, int r) {
    if(l == 1 && r == n) {
	cerr << "modify = [" << ql << ", " << qr << "] op = " << op << " " << x << "\n";
    }
    if(ql <= l && r <= qr) return setmul(cur, x), void();
    pushdown(cur, l, r);
    int mid = l + r >> 1;
    if(ql <= mid) modify(cur << 1, ql, qr, op, x, l, mid);
    if(mid < qr) modify(cur << 1 | 1, ql, qr, op, x, mid + 1, r);
    pushup(cur);
}

inline int queryf(int cur, int ql, int qr, int l, int r) {
    if(ql <= l && r <= qr) return fval[cur];
    pushdown(cur, l, r);
    int mid = l + r >> 1;
    int res = 0;
    if(ql <= mid) upd(res, queryf(cur<<1, ql, qr, l, mid));
    if(mid < qr) upd(res, queryf(cur<<1|1, ql, qr, mid+1, r));
    return res;
}

int main() {
    freopen("climb.in", "r", stdin);
    freopen("climb.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    rep(i, 2, n) {
	int fa; cin >> fa; fat[i] = fa;
	adj[fa].pb(i);
    }
    rep(i, 1, n) cin >> w[i];
    rep(i, 1, n) cin >> a[i];
    
    f[1] = 1;
    dfs(1, 0);
    
    build(1, 1, n);

    rep(i, 1, n) {
	if(!f[i]) pre[i] = pre[i-1];
	else upd(pre[i], pre[i-1], f[i]);
    }
    
    cin >> q;

    cout << sum[1] << "\n";

    int sum1 = 0;
    
    while(q--) {
	int u, aa, ww;
	cin >> u >> ww >> aa;

	w[u] = ww;
	a[u] = aa;

	dfncnt=0;

	dfs(1, 0);
	build(1,1,n);
	cout<<sum[1]<<"\n";
	/*
	
	cerr << "query = " << u << " " << ww << " " << aa << " ---------\n";
	if(u != 1) {
	    int osum = psum[fat[u]];
	    int nsum = psum[fat[u]] - w[u] + ww;
	    
	    cerr << "sum = " << fat[u] << " " << psum[fat[u]] << " " << osum << " " <<  nsum << "\n";
	    
	    if(nsum >= mod) nsum -= mod;
	    if(nsum < 0) nsum += mod;

	    
	    psum[fat[u]] = nsum;

	    cerr << "dfn in " << dfn[fat[u]]+1 << " " << dfn[fat[u]]+siz[fat[u]]-1 << " " << (double)osum / nsum << "\n";
	    cerr << "dfn in " << dfn[u] << " " << dfn[u] + siz[u] - 1 << " " << (double)ww / w[u] << "\n";
	    
	    modify(1, dfn[fat[u]]+1, dfn[fat[u]]+siz[fat[u]]-1, 1, 1ll*osum*qpow(nsum,mod-2)%mod, 1, n);
	    modify(1, dfn[u], dfn[u]+siz[u]-1, 1, 1ll*ww*qpow(w[u],mod-2)%mod, 1, n);
	}

	int delt = aa - a[u];
	if(delt < 0) delt += mod;
	
	// modify(1, dfn[u], dfn[u]+siz[u]-1, 2, 1ll*ff*delt%mod, 1, n);

	int ff = queryf(1, dfn[u], dfn[u]+siz[u]-1, 1, n);


	rep(i, 1, n) cerr << queryf(1, dfn[i], dfn[i], 1, n) << " \n"[i == n];;
	
	sum1 = (1ll * delt * ff + sum1) % mod;
	
	cout << (sum[1] + sum1) % mod << "\n";
	cerr << 8ll*(sum[1]+sum1)%mod << "\n";

	a[u] = aa;
	w[u] = ww;
	*/
    }
    cout.flush();
    
    return 0;
}
    
