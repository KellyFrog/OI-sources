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

const int N = 2.5e5 + 5;
const int P1 = 998244353;
const int P2 = 1e9 + 7;
const int P3 = 1e9 + 9;

inline int qpow(int x, ll p, ll P) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, q;
int a[N], b[N];
stack<int> s1, s2;
int t[N<<2][3][2], lazy[N<<2][3][2][2], umat[3][2][2], omat[3][2][2], qres[3];
bool vis[N<<2];
vector<pair<int, int>> adj[N];
unsigned long long ans[N<<2];

inline void mul(int tar[3][2], int mat[3][2][2]) {
	int tmp[2];
	memcpy(tmp, tar[0], sizeof tar[0]);
	tar[0][0] = (1ll * tmp[0] * mat[0][0][0]) % P1;
	tar[0][1] = (1ll * tmp[0] * mat[0][0][1] + 1ll * tmp[1] * mat[0][1][1]) % P1;
	memcpy(tmp, tar[1], sizeof tar[1]);
	tar[1][0] = (1ll * tmp[0] * mat[1][0][0]) % P2;
	tar[1][1] = (1ll * tmp[0] * mat[1][0][1] + 1ll * tmp[1] * mat[1][1][1]) % P2;
	memcpy(tmp, tar[2], sizeof tar[2]);
	tar[2][0] = (1ll * tmp[0] * mat[2][0][0]) % P3;
	tar[2][1] = (1ll * tmp[0] * mat[2][0][1] + 1ll * tmp[1] * mat[2][1][1]) % P3;
}

inline void mul(int tar[3][2][2], int mat[3][2][2]) {
	int tmp[2][2];
	memcpy(tmp, tar[0], sizeof tar[0]);
	tar[0][0][0] = (1ll * tmp[0][0] * mat[0][0][0]) % P1;
	tar[0][0][1] = (1ll * tmp[0][0] * mat[0][0][1] + tmp[0][1]) % P1;
	memcpy(tmp, tar[1], sizeof tar[1]);
	tar[1][0][0] = (1ll * tmp[0][0] * mat[1][0][0]) % P2;
	tar[1][0][1] = (1ll * tmp[0][0] * mat[1][0][1] + tmp[0][1]) % P2;
	memcpy(tmp, tar[2], sizeof tar[2]);
	tar[2][0][0] = (1ll * tmp[0][0] * mat[2][0][0]) % P3;
	tar[2][0][1] = (1ll * tmp[0][0] * mat[2][0][1] + tmp[0][1]) % P3;
}

inline void setlazy(int o, int mat[3][2][2]) {
	vis[o] = 1;
	mul(t[o], mat);
	mul(lazy[o], mat);
}

inline void pushdown(int o) {
	if(!vis[o]) return;
	setlazy(o << 1, lazy[o]);
	setlazy(o << 1 | 1, lazy[o]);
	memcpy(lazy[o], umat, sizeof lazy[o]);
	vis[o] = 0;
}

inline void pushup(int o) {
	t[o][0][0] = (t[o << 1][0][0] + t[o << 1 | 1][0][0]) % P1;
	t[o][0][1] = (t[o << 1][0][1] + t[o << 1 | 1][0][1]) % P1;
	t[o][1][0] = (t[o << 1][1][0] + t[o << 1 | 1][1][0]) % P2;
	t[o][1][1] = (t[o << 1][1][1] + t[o << 1 | 1][1][1]) % P2;
	t[o][2][0] = (t[o << 1][2][0] + t[o << 1 | 1][2][0]) % P3;
	t[o][2][1] = (t[o << 1][2][1] + t[o << 1 | 1][2][1]) % P3;
}

inline void modify(int o, int p, int vec[3][2], int l, int r) {
	if(l == r) {
		memcpy(t[o], vec, sizeof t[o]);
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if(p <= mid) modify(o << 1, p, vec, l, mid);
	else modify(o << 1 | 1, p, vec, mid + 1, r);
	pushup(o);
}

inline void modify(int o, int ql, int qr, int mat[3][2][2], int l, int r) {
	if(ql <= l && r <= qr) return setlazy(o, mat), void();
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) modify(o << 1, ql, qr, mat, l, mid);
	if(mid < qr) modify(o << 1 | 1, ql, qr, mat, mid + 1, r);
	pushup(o);
}

inline void query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		qres[0] = (qres[0] + t[o][0][1]) % P1;
		qres[1] = (qres[1] + t[o][1][1]) % P2;
		qres[2] = (qres[2] + t[o][2][1]) % P3;
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) query(o << 1, ql, qr, l, mid);
	if(mid < qr) query(o << 1 | 1, ql, qr, mid + 1, r);
}

inline void build(int o, int l, int r) {
	memcpy(lazy[o], umat, sizeof lazy[o]);
	if(l == r) return;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int tp;
	cin >> tp >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	a[0] = b[0] = n+1;

	cin >> q;
	rep(i, 1, q) {
		int l, r; cin >> l >> r;
		adj[r].emplace_back(l, i);
	}

	umat[0][0][0] = umat[0][1][1] = 1;
	umat[1][0][0] = umat[1][1][1] = 1;
	umat[2][0][0] = umat[2][1][1] = 1;
	omat[0][0][0] = omat[0][0][1] = omat[0][1][1] = 1;
	omat[1][0][0] = omat[1][0][1] = omat[1][1][1] = 1;
	omat[2][0][0] = omat[2][0][1] = omat[2][1][1] = 1;

	s1.push(0), s2.push(0);

	int inv1 = qpow(1ll * P2 * P3 % P1, P1-2, P1);
	int inv2 = qpow(1ll * P1 * P3 % P2, P2-2, P2);
	int inv3 = qpow(1ll * P1 * P2 % P3, P3-2, P3);

	build(1, 1, n);
	rep(i, 1, n) {
		int cmat[3][2][2], cvec[3][2];
		while(a[s1.top()] < a[i]) {
			memset(cmat, 0, sizeof cmat);
			int v = a[s1.top()];
			cmat[0][0][0] = 1ll * qpow(v, P1-2, P1) * a[i] % P1;
			cmat[1][0][0] = 1ll * qpow(v, P2-2, P2) * a[i] % P2;
			cmat[2][0][0] = 1ll * qpow(v, P3-2, P3) * a[i] % P3;
			cmat[0][1][1] = cmat[1][1][1] = cmat[2][1][1] = 1;
			int qr = s1.top();
			s1.pop();
			int ql = s1.top() + 1;
			modify(1, ql, qr, cmat, 1, n);
		}
		while(b[s2.top()] < b[i]) {
			memset(cmat, 0, sizeof cmat);
			int v = b[s2.top()];
			cmat[0][0][0] = 1ll * qpow(v, P1-2, P1) * b[i] % P1;
			cmat[1][0][0] = 1ll * qpow(v, P2-2, P2) * b[i] % P2;
			cmat[2][0][0] = 1ll * qpow(v, P3-2, P3) * b[i] % P3;
			cmat[0][1][1] = cmat[1][1][1] = cmat[2][1][1] = 1;
			int qr = s2.top();
			s2.pop();
			int ql = s2.top() + 1;
			modify(1, ql, qr, cmat, 1, n);
		}

		s1.push(i), s2.push(i);

		memset(cvec, 0, sizeof cvec);
		cvec[0][0] = 1ll * a[i] * b[i] % P1;
		cvec[1][0] = 1ll * a[i] * b[i] % P2;
		cvec[2][0] = 1ll * a[i] * b[i] % P3;
		
		modify(1, i, cvec, 1, n);
		modify(1, 1, n, omat, 1, n);

		for(auto [l, id] : adj[i]) {
			memset(qres, 0, sizeof qres);
			query(1, l, n, 1, n);
			__int128 PP = (__int128)P1 * P2 * P3;
			__int128 a = 1ll * qres[0] * inv1 % P1;
			__int128 b = 1ll * qres[1] * inv2 % P2;
			__int128 c = 1ll * qres[2] * inv3 % P3;
			ans[id] = (unsigned long long)((a * P2 * P3 + b * P1 * P3 + c * P1 * P2) % PP);
		}
	}
	rep(i, 1, q) cout << ans[i] << "\n";

	return 0;
}
