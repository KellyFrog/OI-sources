#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e3 + 5;

int n, m;
ll a[N][N], b[N], c[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    freopen("opt.in", "r", stdin);
    freopen("opt.out", "w", stdout);

    cin >> n >> m;
    rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
    ll ans = 0;
    rep(i, 1, n) {
	memset(c, 0, sizeof c);
	per(j, 1, m) {
	    c[j] = max(0ll, max(c[j+1], a[i][j]) - b[j]);
	    b[j] = c[j] + b[j] - c[j+1];
	    assert(b[j] >= 0);
	}
	ans += c[1];
	
    }

    cout << ans << endl;

    return 0;
}
