// Problem: AT_agc007_d [AGC007D] Shik and Game
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc007_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

const int N = 1e5 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, e, t;
int que[N], ph = 1, pt = 0;
ll f[N], pos[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> e >> t;
	rep(i, 1, n) cin >> pos[i];
	pos[n+1] = e;

	memset(f, 0x3f, sizeof f);
	f[0] = 0, que[++pt] = 1;
	ll mi = inf;
	int p = 1;
	rep(i, 1, n + 1) {
		while(2 * (pos[i] - pos[p]) > t) {
			mi = min(mi, -2 * pos[p] - pos[p-1] + f[p-1]);
			++p;
		}
		while(ph <= pt && que[ph] < p) ++ph;
		while(ph <= pt && -pos[que[pt]-1] + f[que[pt]-1] > -pos[i-1] + f[i-1]) --pt;
		que[++pt] = i;
		if(ph <= pt) {
			int j = que[ph];
			f[i] = min(f[i], pos[i] - pos[j-1] + t + f[j-1]);
		}
		f[i] = min(f[i], 3 * pos[i] + mi);
	}

	cout << min(f[n+1], f[n] + e - pos[n]) << "\n";
	
	return 0;
}
