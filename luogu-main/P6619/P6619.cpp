// Problem: P6619 [省选联考 2121 A/B 卷] 冰火战士
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6619
// Memory Limit: 512 MB
// Time Limit: 3000 ms
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

const int N = 1 << 22 | 255;

int n, m = 1 << 22;
int op[N], tp[N], x[N], y[N];
ll t[2][N];
int c[2];
ll s[2];
	vector<int> a;

inline int lowbit(int x) { return x & (-x); }
inline void add(int p, int x, ll v) { for(int x0 = x; x0 <= m; x0 += lowbit(x0)) t[p][x0] += v; }

void solve() {
	ll sum1 = 0, sum2 = 0;
	int pos = 0;
	per(i, 0, 21) {
		ll v1 = t[0][pos + (1 << i)] + sum1;
		ll v2 = t[1][pos + (1 << i)] + sum2;
		v2 = s[1] - v2;
		if(v1 <= v2) {
			sum1 += t[0][pos + (1 << i)];
			sum2 += t[1][pos + (1 << i)];
			pos += 1 << i;
		}
	}
	ll ans = min(sum1, s[1]-sum2);
	sum1 = 0, sum2 = 0;
	for(int x0 = pos+1; x0; x0 -= lowbit(x0)) {
		sum1 += t[0][x0];
		sum2 += t[1][x0];
	}
	ans = max(ans, min(sum1, s[1]-sum2));
	pos = 0;
	sum1 = 0, sum2 = 0;
	per(i, 0, 21) {
		ll v1 = t[0][pos + (1 << i)] + sum1;
		ll v2 = t[1][pos + (1 << i)] + sum2;
		v2 = s[1] - v2;
		if((v1 <= ans && v2 >= ans) || min(v1, v2) == ans) {
			sum1 += t[0][pos + (1 << i)];
			sum2 += t[1][pos + (1 << i)];
			pos += 1 << i;
		}
	}
	assert(min(sum1, s[1]-sum2) == ans);
	if(ans == 0) cout << "Peace" << "\n";
	else cout << a[min((int)a.size(), pos+1)-1]-1 << " " << 2*ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) {
		cin >> op[i];
		if(op[i] == 1) cin >> tp[i] >> x[i] >> y[i], a.pb(x[i] + tp[i]);
		else cin >> tp[i];
	}
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	rep(i, 1, n) {
		if(op[i] == 1) x[i] = lower_bound(a.begin(), a.end(), x[i] + tp[i]) - a.begin() + 1;
	}
	rep(i, 1, n) {
		if(op[i] == 1) {
			add(tp[i], x[i], y[i]);
			++c[tp[i]], s[tp[i]] += y[i];
		} else {
			int p = tp[i];
			add(tp[p], x[p], -y[p]);
			--c[tp[p]], s[tp[p]] -= y[p];
		}
		solve();
	}
	
	return 0;
}
