#include "minerals.h"
#include <vector>
#include <iostream>

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

int a[N], b[N], c[N];
bool vis[N<<1];

int query(int x) {
	vis[x] ^= 1;
	return Query(x);
}

void solve(int al, int ar, int bl, int br, bool flag) {
	if(al == ar) {
		Answer(a[al], b[bl]);
		return;
	}
	int mid = al + ar >> 1;
	int t = 0;
	rep(i, al, mid) t = query(a[i]);
	int p1 = bl-1, p2 = br+1;
	rep(i, bl, br) {
		int t0 = t;
		if((t0 != (t = query(b[i])) ^ flag)) c[--p2] = b[i];
		else c[++p1] = b[i];
	}
	rep(i, mid+1, ar) query(a[i]);
	rep(i, bl, br) b[i] = c[i];
	solve(al, mid, bl, bl+mid-al, flag ^ 1);
	solve(mid+1, ar, bl+mid-al+1, br, flag ^ 1);
}

void Solve(int n) {
	vector<int> s, t;
	int c = 0, p1 = 0, p2 = 0;
	rep(i, 1, 2*n) {
		if(c != query(i)) ++c, a[++p1] = i;
		else b[++p2] = i;
	}
	solve(1, n, 1, n, 1);
}

}

void Solve(int n) {
	sol::Solve(n);
}
