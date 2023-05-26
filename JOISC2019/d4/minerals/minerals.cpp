#include "minerals.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace sol {
const int N = 1e6 + 5;
const long double magic = (3.0 - sqrt(5)) / 2;

int a[N], b[N], c[N];
int las;
bool vis[N<<1];

int query(int x) {
	vis[x] ^= 1;
	return las = Query(x);
}

void solve(int al, int ar, int bl, int br) {
	if(al == ar) {
		Answer(a[al], b[bl]);
		return;
	}
	int p = magic * ar + (1 - magic) * al;
	bool flag = vis[a[al]];
	rep(i, al, p) query(a[i]);
	int p1 = bl-1, p2 = br+1;
	rep(i, bl, br) {
		int t0 = las;
		if(p1 == bl+p-al) c[--p2] = b[i];
		else if(p2 == bl+p-al+1) c[++p1] = b[i];
		else if((t0 != query(b[i]) ^ flag)) c[--p2] = b[i];
		else c[++p1] = b[i];
	}
	rep(i, bl, br) b[i] = c[i];
	solve(al, p, bl, bl+p-al);
	solve(p+1, ar, bl+p-al+1, br);
}

void Solve(int n) {
	vector<int> s, t;
	int c = 0, p1 = 0, p2 = 0;
	rep(i, 1, 2*n) {
		if(c != query(i)) ++c, a[++p1] = i;
		else b[++p2] = i;
	}
	solve(1, n, 1, n);
}

}

void Solve(int n) {
	sol::Solve(n);
}
