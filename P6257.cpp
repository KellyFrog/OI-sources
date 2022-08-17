// Problem: P6257 [ICPC2019 WF]First of Her Name
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6257
// Memory Limit: 500 MB
// Time Limit: 10000 ms
// Create Time: 2022-08-16 16:40:50
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

const int N = 2e6 + 5;

int n, m, q;
char s[N], t[N];
vector<int> adj[N];
int son[N][26], fail[N], rt, tt, cnt[N], pos[N];
int que[N], ph=1, pt;

void insert(int id) {
	m = strlen(t + 1);
	reverse(t + 1, t + m + 1);
	if(!rt) rt = ++tt;
	int o = rt;
	rep(i, 1, m) {
		if(!son[o][t[i]-'A']) son[o][t[i]-'A'] = ++tt;
		o = son[o][t[i]-'A'];
	}
	pos[id] = o;
}

void buildfail() {
	rep(i, 0, 25) {
		if(!son[rt][i]) son[rt][i] = rt;
		else fail[son[rt][i]] = rt, que[++pt]=son[rt][i];
	}
	while(ph <= pt) {
		int o = que[ph++];
		rep(i, 0, 25) {
			if(!son[o][i]) son[o][i] = son[fail[o]][i];
			else fail[son[o][i]] = son[fail[o]][i], que[++pt] = son[o][i];
		}
	}
}

inline void dfs(int u, int fa, int o) {
	o = son[o][s[u]-'A'];
	++cnt[o];
	for(int v : adj[u]) dfs(v, u, o);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) {
		int f; cin >> s[i] >> f;
		adj[f].pb(i);
	}
	rep(i, 1, q) {
		cin >> t+1;
		insert(i);
	}
	buildfail();
	dfs(1, 0, rt);
	per(i, 1, tt) cnt[fail[que[i]]] += cnt[que[i]];
	rep(i, 1, q) cout << cnt[pos[i]] << "\n";
	
	return 0;
}
