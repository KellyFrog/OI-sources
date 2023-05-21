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

const int N = 1e6 + 5;

int n, m;
ll a[N], b[N], c[N], sa[N];
ll d[N], e[N], f[N], sb[N];
ll dt[N];
int p1[N], p2[N];
vector<int> adj[N];
set<int> st;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, n) cin >> a[i] >> b[i] >> c[i];
	rep(i, 1, m) cin >> d[i] >> e[i] >> f[i];
	rep(i, 1, n) sa[i] = sa[i-1] + a[i];
	rep(i, 1, m) sb[i] = sb[i-1] + d[i];
	rep(i, 1, n) p1[i] = upper_bound(sb, sb + m + 1, b[i]-sa[i]) - sb - 1;
	rep(i, 1, m) p2[i] = upper_bound(sa, sa + n + 1, e[i]-sb[i]) - sa - 1;
	rep(i, 1, m) if(p2[i] >= 0) {
	   	adj[p2[i]].pb(i);
	}
	rep(i, 1, n) {
		for(int j : adj[i-1]) {
			if(f[j] >= 0) dt[j] += f[j], st.emplace(j);
		}
		if(p1[i] >= 0) {
			if(c[i] <= 0) {
				dt[0] += c[i];
				dt[p1[i]+1] -= c[i];
				st.emplace(0), st.emplace(p1[i]+1);
			} else {
				dt[0] += c[i];
				st.emplace(0);
				ll df = c[i];
				auto it = st.lower_bound(p1[i]+1);
				while(df && it != st.end()) {
					int j = *it;
					ll t = min(df, dt[j]);
					dt[j] -= t, df -= t;
					if(df) it = st.erase(it);
				}
			}
		}
		for(int j : adj[i-1]) {
			if(f[j] < 0) {
				ll tt = min(dt[j], -f[j]);
				ll df = -f[j] - tt;
				dt[j] -= tt;
				auto it = st.lower_bound(j);
				while(df && it != st.end()) {
					int k = *it;
					ll t = min(df, dt[k]);
					df -= t, dt[k] -= t;
					if(df) it = st.erase(it);
				}
			}
		}
	}
	ll ans = 0;
	rep(i, 0, m) {
		ans += dt[i] + (p2[i] == n) * f[i];
	}
	cout << ans << "\n";

	return 0;
}
