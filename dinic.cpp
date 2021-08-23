template<const int N, const int M> 
class Flow {
	const ll inf = 1e18;
	int head[N], nxt[M<<1], to[M<<1];
	ll wgt[M<<1];
	int tot = 0;
	int dis[N];
	int s, t;
	
	
	
	
	inline bool bfs() {
		memset(dis, 0, sizeof dis);
		static int que[N]; int hea = 1, tail = 0;
		dis[s] = 1;
		que[++tail] = s;
		while(hea <= tail) {
			int u = que[hea++];
			for(int e = head[u]; e; e = nxt[e]) {
				int v = to[e];
				ll w = wgt[e];
				if(w != 0 && dis[v] == 0) {
					dis[v] = dis[u] + 1;
					que[++tail] = v;
				}
			}
		}
		return dis[t];
	}
	
	inline ll dfs(int u, ll in) {
		if(u == t) return in;
		ll res = 0;
		for(int e = head[u]; e; e = nxt[e]) {
			int v = to[e];
			ll w = wgt[e];
			if(w && dis[v] == dis[u] + 1) {
				ll cur = dfs(v, min(in, w));
				in -= cur;
				res += cur;
				wgt[e] -= cur;
				wgt[e^1] += cur;
			}
		}
		return res ? res : dis[u] = 0, res;
	}
	
	public:
	
	Flow() : tot(1), s(-1), t(-1) {}
	
	inline void addedge(int u, int v, ll w) {
		nxt[++tot] = head[u];
		to[tot] = v;
		wgt[tot] = w;
		head[u] = tot;
	}
	
	inline ll solve(int s0, int t0) {
		s = s0;
		t = t0;
		assert(s != t);
		ll ans = 0;
		while(bfs()) ans += dfs(s, inf);
		return ans;
	}
};