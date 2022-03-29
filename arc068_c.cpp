// Problem: E - Snuke Line
// Contest: AtCoder - AtCoder Regular Contest 068
// URL: https://atcoder.jp/contests/arc068/tasks/arc068_c
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

/*
 * Author: chenkaifeng @BDFZ
 */
 
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
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 5e5 + 5;
const int M = 1e5 + 5;

vector<int> qry[N], opt[N];
int n, m;
int ql[N], qr[N];
int delt[N];
ll ans[N];
int t[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= m; x0 += lowbit(x0)) t[x0] += val; }
inline int query(int x) { int res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += t[x0]; return res; }

void solve(int d) {
    for(int i = d; i <= m; i += d) {
	ans[d] += delt[i];
	qry[i-d].pb(i);
    }
}

int main() {
    // freopen("movie.in", "r", stdin);
    // freopen("movie.out", "w", stdout);
    
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(15); cerr << fixed << setprecision(15);

    cin >> n >> m;
    rep(i, 1, n) {
	cin >> ql[i] >> qr[i];
	opt[ql[i]].pb(qr[i]);
	++delt[ql[i]], --delt[qr[i]+1];
    }
    rep(i, 1, m) delt[i] += delt[i-1];
    rep(i, 1, m) solve(i);
    int tot = 0;
    rep(i, 1, m) {
	for(int r : opt[i]) add(r, 1), ++tot;
	for(int r : qry[i]) {
	    ans[r-i] -= tot - query(r-1);
	}
    }
    rep(i, 1, m) cout << ans[i] << "\n";
    cout.flush();
    
    return 0;
}
