#include <bits/stdc++.h>

using namespace std;

template <typename T> void inline read(T &x) {
	x = 0; int f = 1; char s = getchar();
	while (s < '0' && s > '9') { if (s == '-') f = -1; s = getchar(); }
	while (s >= '0' && s <= '9') x = x * 10 + s - '0', s = getchar();
	x *= f;
}

template <typename T> void inline chkMax(T &x, T y) { if (y > x) x = y; }
template <typename T> void inline chkMin(T &x, T y) { if (y < x) x = y; }

#define pb push_back
#define fi first
#define se second
#define mp make_pair

const int N = 5005;

typedef long long LL;

int m, n, q;
LL ans;

typedef pair<int, int> PII;

PII a[N];

set<PII> s;


struct E{
	int a, b, c;
} c[N], d[N];

int t1, t2;

int U, D, x, y;

void inline clear() {
	t1 = t2 = 0;
	s.clear();
}

void inline upd(int i) {
	if (a[i].se > y) {
		chkMin(U, a[i].se - y);
	}
	if (a[i].se < y) {
		chkMin(D, y - a[i].se);
	}
}

LL inline calc1(int i, int j) {
	return c[i].a + d[j].a;
}

LL inline calc2(int i, int j) {
	return min(c[i].b, d[j].b) + min(c[i].c, d[j].c);
}


int main() {
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	int T; read(T);
	while (T--) {
		read(m), read(n);
		for (int i = 1; i <= n; i++) read(a[i].fi), read(a[i].se), s.insert(a[i]);
		a[++n] = mp(0, 0), a[++n] = mp(m, 0);
		sort(a + 1, a + 1 + n);
		read(q);
		while (q--) {
			read(x), read(y);
			if (x == 0 || y == 0 || x == m || y == m || s.count(mp(x, y))) puts("0");
			else {
				ans = 2;
				int p = 0;
				while (p < n && a[p + 1].fi <= x) p++;
				U = m - y, D = y;
				t1 = t2 = 0;
				for (int i = p; i; i--) {
					if ((i == p || a[i + 1].fi != a[i].fi) && a[i].fi != x) {
						c[++t1] = (E) { x - a[i].fi, U, D };
					}
					upd(i);
					if (a[i].se == y) break;
				}
				U = m - y, D = y;
				for (int i = p + 1; i <= n; i++) {
					if (i == p + 1 || a[i].fi != a[i - 1].fi) {
						d[++t2] = (E) { a[i].fi - x, U, D };
					}
					upd(i);
					if (a[i].se == y) break;
				}
				for (int i = 1, j = t2; i <= t1; i++) {
					LL v1 = calc1(i, j), v2 = calc2(i, j);
					while (v1 > v2 && j > 1) {
						j--;
						v1 = calc1(i, j), v2 = calc2(i, j);
					}
					chkMax(ans, min(v1, v2));
				}
				for (int i = 1, j = t2; i <= t1; i++) {
					LL v1 = calc1(i, j), v2 = calc2(i, j);
					while (j > 1 && calc1(i, j - 1) >= calc2(i, j - 1)) {
						j--;
						v1 = calc1(i, j), v2 = calc2(i, j);
					}
					chkMax(ans, min(v1, v2));
				}
				printf("%lld\n", ans * ans);
			}
		}
		clear();
	}
	return 0;
}

