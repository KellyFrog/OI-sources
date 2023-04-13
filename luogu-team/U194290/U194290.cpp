// Problem: U194290 【HDOI2021提高组T2】
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U194290
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-12-12 17:20:29
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

const int N = 5e5 + 5;
const int M = N * 22;
const int P = 20050801;
const int inf = 0x3f3f3f3f;

int n;
char s[N];
int nxt[N], dep[N], a[N], b[N], ans1 = inf, ans2;
int rt[N], sum[M], cnt[M], ls[M], rs[M], mi[M], mx[M], tt;

inline int newnode() {
	int o = ++tt;
	sum[o] = cnt[o] = ls[o] = rs[o] = 0;
	mi[o] = inf, mx[o] = -inf;
	return o;
}

inline void pushup(int o) {
	cnt[o] = cnt[ls[o]] + cnt[rs[o]];
	sum[o] = (sum[ls[o]] + sum[rs[o]]) % P;
	mi[o] = min(mi[ls[o]], mi[rs[o]]);
	mx[o] = max(mx[ls[o]], mx[rs[o]]);
}

inline void ins(int& o, int p, int l, int r) {
	if(!o) o = newnode();
	if(l == r) {
		++cnt[o];
		sum[o] = (sum[o] + b[p]) % P;
		mi[o] = min(mi[o], b[p]);
		mx[o] = max(mx[o], b[p]);
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) ins(ls[o], p, l, mid);
	else ins(rs[o], p, mid + 1, r);
	pushup(o);
}

inline void merge(int& o1, int o2, int l, int r, int d) {
	if(!o1 || !o2) return o1 += o2, void();
	if(l == r) {
		assert(cnt[o1] && cnt[o2]);
		ans1 = 0;
		cnt[o1] += cnt[o2];
		sum[o1] = (sum[o1] + sum[o2]) % P;
		return;
	}
	ans1 = min(ans1, mi[rs[o1]] - mx[ls[o2]]);
	ans1 = min(ans1, mi[rs[o2]] - mx[ls[o1]]);
	ans2 = (ans2 + (1ll * cnt[ls[o1]] * sum[rs[o2]] + 1ll * cnt[ls[o2]] * sum[rs[o1]] - 1ll * cnt[rs[o1]] * sum[ls[o2]] - 1ll * cnt[rs[o2]] * sum[ls[o1]]) % P * d) % P;
	int mid = l + r >> 1;
	merge(ls[o1], ls[o2], l, mid, d);
	merge(rs[o1], rs[o2], mid + 1, r, d);
	pushup(o1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	cin >> (s + 1);
	rep(i, 1, n) cin >> a[i];
	reverse(s + 1, s + n + 1);
	reverse(a + 1, a + n + 1);

	rep(i, 1, n) b[i] = a[i];
	sort(b + 1, b + n + 1);
	int m = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	
	rep(i, 2, n) {
		int j = nxt[i-1];
		while(j && s[j+1] != s[i]) j = nxt[j];
		j += s[j+1] == s[i];
		nxt[i] = j;
	}
	rep(i, 1, n) dep[i] = dep[nxt[i]] + 1;
	mx[0] = -inf, mi[0] = inf;
	per(i, 1, n) ins(rt[i], a[i], 1, m);
	per(i, 1, n) if(nxt[i]) merge(rt[nxt[i]], rt[i], 1, m, dep[nxt[i]]);

	cout << (ans1 == inf ? -1 : ans1) << " " << (ans2 + P) % P << "\n";
	
	return 0;
}
