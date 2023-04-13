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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1.5e6 + 5;
const int P = 1e9 + 7;

struct L {
	int op;
	int x, y;
	int val;
	L(int op, int x, int y, int val) : op(op), x(x), y(y), val(val) {}
	L() {}
};

int n, m, H;
L op[N<<1]; int opp;
int lson[N], rson[N], lim[N], f[N];
int uni[N], rt[N], tot;

inline int getid(int i, int j) { return (i-1) * m + j; }
inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

inline void dfs(int u) {
	if(lson[u] && rson[u]) {
		dfs(lson[u]);
		dfs(rson[u]);
	}
	f[u] = (1ll * f[lson[u]] * f[rson[u]] + (lim[u] - lim[lson[u]]) + (lson[u] == 0)) % P;
}

int main() {
	freopen("level.in", "r", stdin);
	freopen("level.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> H;
	
	rep(i, 1, n) rep(j, 1, m-1) {
		int x; cin >> x;
		op[++opp] = L(1, i, j, x);
	}
	rep(i, 1, n-1) rep(j, 1, m) {
		int x; cin >> x;
		op[++opp] = L(2, i, j, x);
	}
	sort(op + 1, op + opp + 1, [&](const L& x, const L& y) { return x.val < y.val; });
	
	tot = n*m;
	rep(i, 1, n*m) rt[i] = uni[i] = i;
	
	rep(i, 1, opp) {
		int tp = op[i].op;
		int x = op[i].x, y = op[i].y, val = op[i].val;
		int o1, o2;
		if(tp == 1) {
			o1 = getid(x, y);
			o2 = getid(x, y+1);
		} else {
			o1 = getid(x, y);
			o2 = getid(x+1, y);
		}
		
		o1 = find(o1);
		o2 = find(o2);
		if(o1 == o2) continue;
		int ls = rt[o1], rs = rt[o2];
		lim[ls] = lim[rs] = val;
		
		uni[o1] = o2;
		rt[o2] = ++tot;
		lson[rt[o2]] = ls;
		rson[rt[o2]] = rs;
	}
	lim[tot] = H;
	dfs(tot);
	cout << f[tot] << "\n";
	
	return 0;
}
