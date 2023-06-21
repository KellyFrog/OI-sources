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
const int M = 22;

int n, q;
int a[N];
int d[N][M], lst[M];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) {
		rep(j, 0, 19) if(a[i] >> j & 1) d[i][j] = i;
		rep(j, 0, 19) if(a[i] >> j & 1) rep(k, 0, 19) d[i][k] = max(d[i][k], d[lst[j]][k]);
		rep(j, 0, 19) if(a[i] >> j & 1) lst[j] = i;
	}
	while(q--) {
		int x, y; cin >> x >> y;
		bool ok = 0;
		rep(i, 0, 19) if((a[x] >> i & 1) && d[y][i] >= x) ok = 1;
		cout << (ok ? "Shi" : "Fou") << "\n";
	}

	
	return 0;
}
