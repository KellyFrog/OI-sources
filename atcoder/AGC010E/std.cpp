#include <bits/stdc++.h>
using namespace std ;

#define pb push_back
#define SZ(x) ((int)x.size())

const int N = 2010 ;

int vis[N], ok[N][N], in[N], a[N] ;
vector <int> g[N] ;
int n ;

void dfs(int rt) {
	vis[rt] = 1 ;
	for (int i = 1; i <= n; i++)
	if (!vis[i] && ok[rt][i]) {
		in[i]++ ;
		g[rt].pb(i) ;
		dfs(i) ;
	}
}

void Top() {
	priority_queue <int> q ;
	for (int i = 1;  i <= n; i++) if (!in[i]) q.push(i) ;
	while (!q.empty()) {
		int now = q.top() ;
		q.pop() ;
		cout << a[now] << " " ;
		for (int i = 0; i < SZ(g[now]); i++) q.push(g[now][i]) ;
	}
}

signed main(){
	scanf("%d", &n) ;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]) ;
	sort(a + 1, a + n + 1) ;
	for (int i = 1; i <= n; i++)
	for (int j = i + 1; j <= n; j++)
	if (__gcd(a[i], a[j]) != 1) ok[i][j] = ok[j][i] = 1 ;
	for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i) ;//遍历连通块
	Top() ;
}
