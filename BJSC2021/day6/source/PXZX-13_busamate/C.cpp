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

typedef long long LL;

#define pb push_back
#define fi first
#define se second
#define mp make_pair

int a, b, c[6], d[6];

LL ans;

void inline up() {
	memset(d, 0, sizeof d);
	d[1] = c[0];
	d[5] = c[1];
	d[2] = c[2];
	d[3] = c[3];
	d[0] = c[4];
	d[4] = c[5];
	memcpy(c, d, sizeof c);
}

void inline rt() {
	memset(d, 0, sizeof d);
	d[0] = c[0];
	d[5] = c[5];
	d[2] = c[1];
	d[4] = c[2];
	d[1] = c[3];
	d[3] = c[4];
	memcpy(c, d, sizeof c);
}

double k;

bool ok1(int x1, int x2, int y) {
	double x = y / k;
	return x1 <= x && x <= x2;
}

bool ok2(int x, int y1, int y2) {
	double y = x * k;
	return y1 <= y && y <= y2;
}

int main() {
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	read(a), read(b);
	k = (double)b / a;
	for (int i = 0; i < 6; i++) read(c[i]);
	int x = 0, y = 0;
	ans += c[4];
	--a, --b;
	while (x < a || y < b) {
		if (x < a && ok2(x + 1, y, y + 1)) {
			rt();
			x++;
			ans += c[4];
			continue;
		}
		if (y < b && ok1(x, x + 1, y + 1)) {
			up();
			y++;
			ans += c[4];
			continue;
		}
	}
	printf("%lld\n", ans);
	return 0;
}

