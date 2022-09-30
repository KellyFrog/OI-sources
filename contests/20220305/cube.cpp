#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 505;
const int P = 998244353;

int n, m;
int a[N], l[N], r[N];
int f[2][N][N][2], g[2][N][N];

inline void upd(int& x, int y) {
    x += y;
    if(x >= P) x -= P;
}

int main() {
    freopen("cube.in", "r", stdin);
    freopen("cube.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) {
	l[i] = r[i] = i;
	while(l[i] >= 1 && a[l[i]] <= a[i]) --l[i]; ++l[i];
	while(r[i] <= n && a[r[i]] <= a[i]) ++r[i]; --r[i];
	//cerr << l[i] << " " << r[i] << "\n";
    }

    f[0][0][0][0] = 1;

    rep(i, 1, n) {
	memset(f[i&1], 0, sizeof f[i&1]);
	memset(g[i-1&1], 0, sizeof g[i-1&1]);
	rep(j, 0, n) rep(k, 0, m) {
	    g[i-1&1][j][k] = ((ll)(j ? g[i-1&1][j-1][k] : 0) + f[i-1&1][j][k][0] + f[i-1&1][j][k][1]) % P;
	}
	rep(k, 0, m) {
	    rep(j, 0, i-1) {
		upd(f[i&1][i][k][1], f[i-1&1][j][k][0]);
		upd(f[i&1][i][k][1], f[i-1&1][j][k][1]);
	    }
	}
	rep(j, 1, n) {
	    if(i < l[j] || r[j] < i) continue;
	    //fprintf(stderr, "ok i = %d, j = %d\n", i, j);
	    rep(k, 0, m) {
		upd(f[i&1][j][k][0], f[i-1&1][j][k][0]);
		upd(f[i&1][j][k][0], k ? f[i-1&1][j][k-1][1] : 0);
		
		if(i != j) {
		    upd(f[i&1][j][k][0], k ? g[i-1&1][j-1][k-1] : 0);
		}
	    }
	}
	/*
	rep(j, 1, n) rep(k, 0, m) {

	    if(f[n&1][j][k][0] || f[n&1][j][k][1])
		fprintf(stderr, "f[%d][%d][%d] = %d, %d\n", i, j, k, f[n&1][j][k][0], f[n&1][j][k][1]);
	}
	*/
    }
    
    int ans = 0;
    rep(j, 1, n) rep(k, 0, m) {
	upd(ans, f[n&1][j][k][0]);
	upd(ans, f[n&1][j][k][1]);
	//fprintf(stderr, "f[n][%d][%d] = %d, %d\n", j, k, f[n&1][j][k][0], f[n&1][j][k][1]);
    }
    cout << ans << endl;
    
    return 0;
}
