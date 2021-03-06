/*
 * Author: chenkaifeng @BDFZ
 */
 
#include "testlib.h"
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;

int n, m, k;
vector<int> adj[N];
int pans, jans;
int dfn[N], low[N], stk[N], top, scc[N], dfncnt, scccnt;
bool ins[N];

inline void tarjan(int u) {
	stk[++top] = u;
	ins[u] = 1;
	dfn[u] = low[u] = ++dfncnt;
	for(int v : adj[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u]) {
		++scccnt;
		while(1) {
			int x = stk[top--];
			ins[x] = 0;
			scc[x] = scccnt;
			if(x == u) break;
		}
	}
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
	registerTestlibCmd(argc, argv);
    
    n = inf.readInt();
    m = inf.readInt();
    k = inf.readInt();
    
    pans = ouf.readInt();
    jans = ans.readInt();
    
    if(pans > jans + k) quitf(_wa, "wrong answer construction with %d edges exceeded edge limit", pans);
    
    rep(i, 1, m) {
    	int u, v;
    	u = inf.readInt(1, n);
    	v = inf.readInt(1, n);
    	adj[u].pb(v);
    }
    
    rep(i, 1, pans) {
    	int u, v;
    	u = ouf.readInt(1, n, "start vertice of the edge");
    	v = ouf.readInt(1, n, "end vertice of the edge");
    	adj[u].pb(v);
    }
    
    tarjan(1);
    
    rep(i, 1, n) {
    	if(scc[i] != scc[1]) {
    		quitf(_wa, "wrong answer node %d and node %d aren't strongly connected", 1, i);
    	}
    }
    
    quitf(_ok, "ok correct answer, constructed with %d edges", pans);
    
    return 0;
}
