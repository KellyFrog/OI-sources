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

const int N = 2e3 + 5;

int n, m;
int a[N][N], b[N][N];
ll c[N][N], d[N][N], pre[N][N];
int ans[N];
bool vis[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, n) {
		rep(j, 1, m) cin >> a[i][j], b[i][j] = a[i][j] * n;
		rep(j, 1, m) pre[i][j] = pre[i][j-1] + b[i][j];
		ll sum = 0, t = 0;
		rep(j, 1, m) sum += b[i][j], t += a[i][j];
		int p = 0;
		ll cur = 0;
		c[i][0] = 0, d[i][0] = 1;
		rep(j, 1, n) {
			while(cur < t * j) cur += b[i][++p];
			c[i][j] = 1ll * p * b[i][p] - (pre[i][p] - 1ll * j * t);
			d[i][j] = b[i][p];
		}
	}
	ll lasx = 0, lasy = 1;
	rep(i, 1, n) {
		int p = -1;
		int cnt =0 ;
		rep(j, 1, n) if(!vis[j]) {
			assert((__int128)lasy * c[j][i-1] >= (__int128)lasx * d[j][i-1]);
			//c[j][i-1] / d[j][i-1] >= lasx / lasy
			if(p == -1) p = j;
			else {
				//c[j][i] / d[j][i] <= c[p][i] / d[p][i]
				if((__int128)c[j][i] * d[p][i] <= (__int128)c[p][i] * d[j][i]) p = j;
			}
		}
		assert(p != -1);
		ans[i] = p;
		vis[p] = 1;
		if(i != n) cout << c[p][i] << " " << d[p][i] << "\n";
		lasx = c[p][i], lasy = d[p][i];
	}
	rep(i, 1, n) cout << ans[i] << " \n"[i == n];
	
	return 0;
}
