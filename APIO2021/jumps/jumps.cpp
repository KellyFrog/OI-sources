#include "jumps.h"
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

const int N = 2e5 + 5;

int n, a[N];
int ls[N], rs[N], lf[N], rf[N], anc1[N][20], anc2[N][20], st[N], ed[N], t;
int stt[20][N], lg2[N];
int stk[N], top;

inline void dfs(int u, int fa) {
	anc1[u][0] = fa;
	anc2[u][0] = lf[u] ^ rf[u] ^ fa;
	rep(i, 1, 19) {
		anc1[u][i] = anc1[anc1[u][i-1]][i-1];
		anc2[u][i] = anc2[anc2[u][i-1]][i-1];
	}
	st[u] = ++t;
	if(ls[u]) dfs(ls[u], u);
	if(rs[u]) dfs(rs[u], u);
	ed[u] = t;
}

inline int compare(int i, int j) {
	return a[i] > a[j] ? i : j;
}

void init(int N, std::vector<int> H) {
	n = N;
	for(int i = 0; i < n; ++i) a[i+1] = H[i];

	a[0] = a[n+1] = n+1;

	top = 0;
	rep(i, 1, n) {
		while(top && a[stk[top]] < a[i]) --top;
		lf[i] = stk[top];
		stk[++top] = i;
	}
	top = 0;
	per(i, 1, n) {
		while(top && a[stk[top]] < a[i]) --top;
		rf[i] = stk[top];
		stk[++top] = i;
	}
	rep(i, 1, n) {
		if(a[lf[i]] < a[rf[i]]) rs[lf[i]] = i;
		else ls[rf[i]] = i;
	}
	int rt = 0;
	rep(i, 1, n) if(a[i] == n) rt = i;
	dfs(rt, 0);
	rep(i, 1, n) stt[0][i] = i;
	rep(j, 1, 19) rep(i, 1, n) {
		if(i + (1 << j) - 1 > n) break;
		stt[j][i] = compare(stt[j-1][i], stt[j-1][i+(1<<j-1)]);
	}
	lg2[0] = -1;
	rep(i, 1, n) lg2[i] = lg2[i>>1] + 1;
}

inline int LCA(int x, int y) {
	assert(x <= y);
	int k = lg2[y-x+1];
	return compare(stt[k][x], stt[k][y-(1<<k)+1]);
}

int getl(int r, int u) {
	int L = 1, R = r;
	int res = -1;
	while(L <= R) {
		int mid = L + R >> 1;
		int lca = LCA(mid, r);
		if(st[u] <= st[lca] && ed[lca] <= ed[u]) res = mid, R = mid - 1;
		else L = mid + 1;
	}
	return res;
}

int getr(int l, int v) {
	int L = l, R = n;
	int res = -1;
	while(L <= R) {
		int mid = L + R >> 1;
		int lca = LCA(l, mid);
		if(st[lca] <= st[v] && ed[v] <= ed[lca]) res = mid, R = mid - 1;
		else L = mid + 1;
	}
	return res;
}

int minimum_jumps(int A, int B, int C, int D) {
	++A, ++B, ++C, ++D;
	int lca = LCA(B, C);
	int llca = LCA(C, D);
	if(!(st[llca] <= st[lca] && ed[lca] <= ed[llca])) return -1;
	int L = max(A, getl(B, llca));
	int v = LCA(L, B);
	int R = min(D, getr(C, v));
	int u = LCA(C, R);
	int ans = 0;
	per(i, 0, 19) {
		int w = anc2[v][i];
		if(w && st[u] <= st[w] && ed[w] <= ed[u]) v = w, ans += 1 << i;
	}
	if(C <= v) return ans;
	if(C <= anc1[v][0]) return ans + 1;
	int w = anc2[v][0];
	if(st[llca] <= st[w] && ed[w] <= ed[llca]) {
		if(C <= w) return ans + 1;
		return ans + 2;
	}
	per(i, 0, 19) {
		int w = anc1[v][i];
		if(w && st[u] <= st[w] && ed[w] <= ed[u]) v = w, ans += 1 << i;
	}

	return ans;
}
