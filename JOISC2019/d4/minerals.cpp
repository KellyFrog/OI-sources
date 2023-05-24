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
	if(ar == al + 1) {
		cerr << a[al] << " " << a[ar] << "\n";
		cerr << b[bl] << " " << b[br] << "\n";
		int t = las;
		if(!vis[a[al]]) query(a[al]);
		if(vis[b[bl]]) {
			if(t == las) {
				Answer(a[al], b[bl]);
				Answer(a[ar], b[br]);
			} else {
				Answer(a[ar], b[bl]);
				Answer(a[al], b[br]);
			}
		} else {
			if(t == query(b[bl])) {
				Answer(a[al], b[bl]);
				Answer(a[ar], b[br]);
			} else {
				Answer(a[ar], b[bl]);
				Answer(a[al], b[br]);
			}
		}
		return;
	}
	int p = magic * ar + (1 - magic) * al;
	if(vis[a[al]] == vis[b[bl]]) {
		bool flag = vis[a[al]];
		int t = 0;
		rep(i, al, p) t = query(a[i]);
		int p1 = bl-1, p2 = br+1;
		rep(i, bl, br) {
			int t0 = t;
			if((t0 != (t = query(b[i])) ^ flag)) c[--p2] = b[i];
			else c[++p1] = b[i];
		}
		rep(i, bl, br) b[i] = c[i];
	} else {
		if(!vis[a[al]]) rep(i, al, ar) swap(a[i], b[i-al+bl]);
		int t = 0;
		rep(i, al, p) t = query(a[i]);
		int p1 = bl-1, p2 = br+1;
		rep(i, bl, br) {
			int t0 = t;
			if(t0 == (t = query(b[i]))) c[--p2] = b[i];
			else c[++p1] = b[i];
		}
		rep(i, bl, br) b[i] = c[i];
	}
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
