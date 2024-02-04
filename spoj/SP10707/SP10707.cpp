// Problem: COT2 - Count on a tree II
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/SP10707
// Memory Limit: 1 MB
// Time Limit: 1210 ms
// Create Time: 2024-02-04 10:19:43
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

const int N = 4e4 + 5;

int n, m, q;
int a[N], b[N];
vector<int> adj[N];
int ans[N][20];

inline void dfs(int u, int fa) {
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	
	
	return 0;
}
