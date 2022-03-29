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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e6 + 5;

int pre[N], nxt[N], cnt[N];
int siz, phead, ptail, pL, pR;
int n, m, k, t;
int a[N], b[N];
bool vis[N];
vector<int> adj[N];

void solve() {
	// memset(a, 0, sizeof a);
	// memset(b, 0, sizeof b);
	phead = ptail = pL = pR = 0;
	// rep(i, 0, (int)1e6) adj[i].clear();
	
	// cerr << "solve" << "\n";
	bool fucked = 0;
	cin >> m >> n >> k;
	rep(i, 1, n) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1);
	t = unique(b + 1, b + n + 1) - b - 1;
	
	rep(i, 1, n) pre[i] = i-1, nxt[i] = i+1;
	pre[1] = -1, nxt[n] = -1;
	nxt[0] = 1;
	rep(i, 1, n) cnt[a[i]] = 0, adj[a[i]].clear();
	rep(i, 1, n) adj[a[i]].pb(i), ++cnt[a[i]];
	rep(i, 1, n) vis[i] = 0;
	siz = 0;
	
	auto movep = [&]() {
		++pL;
		pR = upper_bound(b + 1, b + t + 1, b[pL] + k - 1) - b - 1;
		// cerr << "get r = " << b[pR] << "\n";
		for(int p : adj[b[pR]]) {
			// cerr << "get pos = " << p << "\n";
			if(fucked) p = n-p+1;
			if(vis[p]) continue;
			if(phead <= p && (ptail == -1 || p < ptail)) {
				vis[p] = 1;
				--cnt[a[p]];
				--siz;
			}
		}
	};
	
	pL = 0;
	movep();
	phead = 0, ptail = 1; //  [phead, ptail)
	
	// cerr << "ok" << "\n";
	
	while(ptail != -1) {
		auto insert = [&]() {
			int p = ptail;
			if(p == -1) return 0;
			if(b[pL] <= a[p] && a[p] <= b[pR] && !vis[p]) {
				vis[p] = 1;
				--cnt[a[p]];
				return 1;
			}
			return 0;
		};
		
		auto movept = [&]() {
			if(phead == 0) {
				phead = 1;
			} else {
				if(vis[phead]) {
					while(phead != -1 && vis[phead]) {
						phead = nxt[phead];
					}
				} else {
					--siz;
					phead = nxt[phead];
					while(phead != -1 && vis[phead]) phead = nxt[phead];
				}
				
			}
			
			while(ptail != -1 && siz < k) {
				while(insert()) ptail = nxt[ptail];
				
				if(ptail == -1) break;
				
				++siz;
				
				ptail = nxt[ptail];
			}
		};
		
		while(ptail != -1 && cnt[b[pL]]) {
			movept();
		}
		
		movep();
	}
	
	// cerr << "final = "; rep(i, 1, n) cerr << vis[i] << " \n"[i == n];
	
	rep(i, 1, n) {
		if(vis[i]) {
			int o1 = pre[i], o2 = nxt[i];
			if(o1 > 0) nxt[o1] = o2;
			if(o2 > 0) pre[o2] = o1;
		}
	}
	
	rep(i, 1, n) {
		if(pre[i] > 0) pre[i] = n-pre[i]+1;
		if(nxt[i] > 0) nxt[i] = n-nxt[i]+1;
		swap(pre[i], nxt[i]);
	}
	reverse(a+1, a+n+1);
	reverse(vis+1, vis+n+1);
	reverse(nxt+1, nxt+n+1);
	fucked = 1;
	
	int pp = -1;
	rep(i, 1, n) if(!vis[i]) { pp = i; break; }
	
	auto print = [&]() {
		if(!phead) return;
		cerr << phead << " " << ptail << "\n";
		int pos = phead;
		while(pos != ptail) {
			if(!vis[pos]) {
				cerr << "a[" << pos << "] = " << a[pos] << "\n";
			}
				pos = nxt[pos];
		}
		cerr << "\n";
		
	};
	
	// print();
	
	
	if(pp == -1) {
		cout << "YES" << "\n";
		return;
	}
	
	phead = 0, ptail = pp;
	
	while(ptail != -1) {
		auto insert = [&]() {
			int p = ptail;
			if(p == -1) return 0;
			if(b[pL] <= a[p] && a[p] <= b[pR]) {
				vis[p] = 1;
				--cnt[a[p]];
				return 1;
			}
			return 0;
		};
		
		auto movept = [&]() {
			if(phead == 0) {
				phead = pp;
			} else {
				if(vis[phead]) {
					while(phead != -1 && vis[phead]) {
						phead = nxt[phead];
					}
				} else {
					--siz;
					phead = nxt[phead];
					while(phead != -1 && vis[phead]) phead = nxt[phead];
				}
				
			}
			
			while(ptail != -1 && siz < k) {
				while(insert()) ptail = nxt[ptail];
				
				if(ptail == -1) break;
				
				++siz;
				
				ptail = nxt[ptail];
			}
		};
		
		while(ptail != -1 && cnt[b[pL]]) {
			movept();
		}
		
		movep();
		
		
		// cerr << "after move " << b[pL] << " " << b[pR] << "\n";
		// print();
	}
	
	rep(i, 1, n) if(!vis[i]) {
		cout << "NO" << "\n";
		return;
	}
	cout << "YES" << "\n";
}

int main() {
	freopen("email.in", "r", stdin);
	freopen("email.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t;
	while(t--) solve();
	
	return 0;
}
