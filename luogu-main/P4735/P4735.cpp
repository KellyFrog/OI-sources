// Problem: P4735 最大异或和
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4735
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// Create Time: 2022-12-12 17:51:10
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

const int N = 6e5 + 5;
const int M = N * 31;

int n, q;
int a[N], pre[N], rt[N], ls[M], rs[M], cnt[M], tt;

inline int newnode(int x) {
	int o = ++tt;
	ls[o] = ls[x], rs[o] = rs[x], cnt[o] = cnt[x];
	return o;
}

inline void ins(int& o1, int o2, int x, int d) {
	o1 = newnode(o2);
	++cnt[o1];
	if(d == -1) return;
	if(x >> d & 1) ins(rs[o1], rs[o2], x, d-1);
	else ins(ls[o1], ls[o2], x, d-1);
}

inline int query(int o1, int o2, int x, int d) {
	if(d == -1) return 0;
	if(x >> d & 1) {
		if(cnt[ls[o1]] - cnt[ls[o2]]) return query(ls[o1], ls[o2], x, d-1) | 1<<d;
		else return query(rs[o1], rs[o2], x, d-1);
	} else {
		if(cnt[rs[o1]] - cnt[rs[o2]]) return query(rs[o1], rs[o2], x, d-1) | 1<<d;
		else return query(ls[o1], ls[o2], x, d-1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q;
	ins(rt[1], rt[0], pre[0], 28);
	rep(i, 1, n) {
		cin >> a[i];
		pre[i] = pre[i-1] ^ a[i];
		ins(rt[i+1], rt[i], pre[i], 28);
	}
	while(q--) {
		char op; cin >> op;
		if(op == 'A') {
			cin >> a[++n];
			pre[n] = pre[n-1] ^ a[n];
			ins(rt[n+1], rt[n], pre[n], 28);
		} else {
			int l, r, x; cin >> l >> r >> x;
			x ^= pre[n];
			cout << query(rt[r], rt[l-1], x, 28) << "\n";
		}
	}

	
	return 0;
}
