#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005
typedef long long ll;
struct node{
    int id;
    ll v;
    node(int id=0, ll v=0):id(id), v(v){}
    bool operator < (const node& n1) const{
        return v > n1.v;
    }
};

struct edge{
    int v,w;
    edge(int v=0, int w=0):v(v),w(w){};
};
vector<edge> adj[MAXN];
ll d[MAXN];
int tot;
int n, m;
void dijkstra(){
    for(int i=1;i<=n;i++) d[i] = 1e18;
    priority_queue<node> q;
    int s = 1;
    d[s] = 0; q.push(node(s,0));

	int u,v,w;
	ll dis;
    while(!q.empty()){
    	u = q.top().id; dis = q.top().v;
        q.pop();
    	if(d[u] != dis) continue;

        // cerr << u << " " << dis << "\n";

		for(int i=0;i<adj[u].size();i++){
      		v = adj[u][i].v; w = adj[u][i].w;
      		++tot;//基本操作次数
      		if(tot >= 1e8) return;
      		if(d[u] + w < d[v]){
      			d[v] = d[u] + w;
                //   cerr << "insert = " << v << " " << d[v] << "\n";
  				q.push(node(v,d[v]));
            }
       	}
    }
}



int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(edge(v, w));
    }
    dijkstra();
    cout << tot << "\n";
    return 0;
}