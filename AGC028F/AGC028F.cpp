// Problem: F - Reachable Cells
// Contest: AtCoder - AtCoder Grand Contest 028
// URL: https://atcoder.jp/contests/agc028/tasks/agc028_f
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Create Time: 2022-07-18 08:25:22
// Input/Output: stdin/stdout
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

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

const int N = 3e3 + 5;

int n;
int a[N][N], b[N][N];
int l[N][N], r[N][N], h[N][N], d[N][N], val[N], pos[N][N], l0[N][N], r0[N][N], pre[N][N], s1[N][N], s2[N][N];
int que[N], ph, pt;
ll ans;

void calc(int n, int m, int p) { //[p+1, n] -> [1, p]

	per(i, 1, m) {
		l[p+1][i] = n+1, r[p+1][i] = 0;
		if(b[p+1][i] != -1) {
			l[p+1][i] = i;
			r[p+1][i] = b[p+1][i+1] == -1 || i+1 > m ? i : r[p+1][i+1];
		}
	}

	per(i, 1, p) per(j, 1, m) {
		l[i][j] = n+1, r[i][j] = 0;
		if(b[i][j] == -1) continue;
		if(j+1 <= m && b[i][j+1] != -1) {
			l[i][j] = min(l[i][j], l[i][j+1]);
			r[i][j] = max(r[i][j], r[i][j+1]);
		}
		if(i+1 <= n && b[i+1][j] != -1) {
			l[i][j] = min(l[i][j], l[i+1][j]);
			r[i][j] = max(r[i][j], r[i+1][j]);
		}
	}
	
	rep(i, 1, p+1) rep(j, 1, m) {
		if(b[i][j] == -1) h[i][j] = n+1;
		else {
			h[i][j] = i;
			if(j-1 >= 1) h[i][j] = min(h[i][j], h[i][j-1]);
			if(i-1 >= 1) h[i][j] = min(h[i][j], h[i-1][j]);
		}
	}
	rep(i, 1, m) {
		l[p+1][i] = n+1, r[p+1][i] = 0;
		if(b[p+1][i] != -1) {
			l[p+1][i] = b[p+1][i-1] == -1 || i-1 < 1 ? i : l[p+1][i-1];
			r[p+1][i] = i;
		}
	}

	rep(i, p+2, n) {
		rep(j, 1, m) {
			l[i][j] = n+1, r[i][j] = 0;
			if(b[i][j] != -1) {
				if(i-1 >= 1 && b[i-1][j] != -1) {
					l[i][j] = min(l[i][j], l[i-1][j]);
					r[i][j] = max(r[i][j], r[i-1][j]);
				}
				if(j-1 >= 1 && b[i][j-1] != -1) {
					l[i][j] = min(l[i][j], l[i][j-1]);
					r[i][j] = max(r[i][j], r[i][j-1]);
				}
			}
		}
	}
	per(i, p+1, n) per(j, 1, m) {
		if(b[i][j] == -1) d[i][j] = 0;
		else {
			d[i][j] = i;
			if(i+1 <= n && b[i+1][j] != -1) d[i][j] = max(d[i][j], d[i+1][j]);
			if(j+1 <= m && b[i][j+1] != -1) d[i][j] = max(d[i][j], d[i][j+1]);
		}
	}

	rep(i, 1, m) rep(j, p+1, n) l0[i][j] = n+1, r0[i][j] = 0;
	rep(i, p+1, n) {
		int lst = 0;
		rep(j, 1, m) {
			if(l[i][j] > r[i][j]) continue;
			rep(k, lst + 1, r[i][j]) if(d[p+1][k] >= i) l0[k][i] = j;
			lst = r[i][j];
		}
		lst = m+1;
		per(j, 1, m) {
			if(l[i][j] > r[i][j]) continue;
			per(k, l[i][j], lst - 1) if(d[p+1][k] >= i) r0[k][i] = j;
			lst = l[i][j];
		}
	}

	rep(i, 1, m) {
		int t = p+1;
		rep(j, i+1, m) {
			while(t <= n && l0[i][t] <= r0[i][t] && l0[j][t] <= r0[j][t] && r0[i][t] < l0[j][t]) ++t;
			if(l0[i][t] > r0[i][t] || l0[j][t] > r0[j][t]) pos[i][j] = n+1;
			else pos[i][j] = t;
		}
	}
	rep(i, p+1, n) rep(j, 1, m) pre[i][j] = pre[i][j-1] + (l[i][j] <= r[i][j] ? max(0, b[i][j]) : 0);
	rep(i, 1, m) {
		s1[i][p] = s2[i][p] = 0;
		rep(j, p+1, d[p+1][i]) {
			s1[i][j] = s1[i][j-1] + pre[j][r0[i][j]];
			s2[i][j] = s2[i][j-1] + pre[j][l0[i][j]-1];
		}
	}

	rep(i, 1, p) {
		ph = 1, pt = 0;
		int sum = 0;

		auto update = [&](int i, int j, int mx) {
			int l = max(mx+1, pos[i][j]);
			int r = min(d[p+1][i], d[p+1][j]);
			if(l <= r) {
				int x = (s1[i][r] - s1[i][l-1]) - (s2[j][r] - s2[j][l-1]);
				val[i] -= x;
				sum -= x;
			}
		};

		auto add = [&](int k) {
			val[k] = s1[k][d[p+1][k]] - s2[k][d[p+1][k]];
			sum += val[k];
			int mx = -1;
			while(ph <= pt && d[p+1][que[pt]] <= d[p+1][k]) {
				update(que[pt], k, mx);
				mx = max(mx, d[p+1][que[pt--]]);
			}
			if(ph <= pt) update(que[pt], k, mx);
			que[++pt] = k;
		};

		r[i][0] = 0;
		int lst = 0, t = 1;
		rep(j, 1, m) val[j] = 0;
		rep(j, 1, m) {
			if(b[i][j] == -1 || l[i][j] > r[i][j]) continue;
			rep(k, lst+1, r[i][j]) if(h[p+1][k] <= i) add(k);
			lst = r[i][j];
			while(ph <= pt && que[ph] < l[i][j]) ++ph;

			while(t < l[i][j]) sum -= val[t++];

			ans += 1ll * b[i][j] * sum;
		}
	}
}

void solve(int l1, int r1, int l2, int r2) {
	if(l1 == r1 && l2 == r2) return;

	if(r1-l1 >= r2-l2) {
		int mid = l1 + r1 >> 1;
		rep(i, l1, r1) rep(j, l2, r2) b[i-l1+1][j-l2+1] = a[i][j];
		calc(r1-l1+1, r2-l2+1, mid-l1+1);
		solve(l1, mid, l2, r2);
		solve(mid+1, r1, l2, r2);
	} else {
		int mid = l2 + r2 >> 1;
		rep(i, l1, r1) rep(j, l2, r2) b[j-l2+1][i-l1+1] = a[i][j];
		calc(r2-l2+1, r1-l1+1, mid-l2+1);
		solve(l1, r1, l2, mid);
		solve(l1, r1, mid+1, r2);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	qio >> n;
	rep(i, 1, n) rep(j, 1, n) qio >> a[i][j];

	solve(1, n, 1, n);

	cout << ans << "\n";

	return 0;
}
