/*
 * Author: chenkaifeng @BDFZ
 */
 
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

const int N = 1e5 + 5;

int n, m, k;
int c[N], a[N], b[N], pos[N];
int t[N], tt;
int stk[N], top;
int cost[N], vis[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m >> k;
    rep(i, 1, n) cin >> c[i];
    rep(i, 1, m) cin >> a[i] >> b[i], pos[a[i]] = i;


    vector<int> opt;

    memset(cost, -1, sizeof cost);
    
    per(i, 1, n) {
	if(vis[i]) continue;
	memset(cost, -1, sizeof cost);
	if(c[a[i]] < c[b[i]]) {
	    if(cost[i] != -1 && cost[i] > k) continue;
	    ++tt;
	    bool f = dfs1(i, i);
	    if(f && cost[i] <= k) {

		top = 0;
		dfs2(i, i);

		// cerr << "dfs = " << i << " " << cost[i] << "\n";
		// per(j, 1, top) cerr << stk[j] << " \n"[j == 1];

		assert(top <= k);
		
		auto update = [&](int p) {
				  assert(!pos[b[p]]);
				  opt.pb(p);
				  pos[a[p]] = 0;
				  pos[b[p]] = p;
				  swap(a[p], b[p]);
				  --k;
			      };
		while(top) update(stk[top--]);
	    }
	}
    }

    cout << opt.size() << "\n";
    for(int p : opt) cout << p << "\n";
    
    return 0;
}
    
