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

const int N = 1e5 + 5;

int n, m, s;
vector<int> adj[N];
int dep[N], win[N], ins[N];
int x;

inline void dfs(int u, int t) {
    assert(t ? u >= x : u < x);
    ins[u] = 1;
    win[u] = 0;
    bool f = 1;
    for(int v : adj[u]) {
        bool ok = 0;
        if(ins[v]) {
            ok = t ^ (dep[v] & 1);
            if(ok) {
                f =0 ;
                win[u] = 1;
            }
        } else {
            ok = t ? v < x : v >= x;
            if(ok) {
                f = 0;
                if(win[v] == -1) {
                    dep[v] = dep[u] + 1;
                    dfs(v, t^1);
                }
                if(!win[v]) win[u] = 1;
            }
        }
        
    }
    if(f) win[u] = 0;
    ins[u] = 0;
}

bool check(int x) {
    memset(dep, 0, sizeof dep);
    memset(win, -1, sizeof win);
    memset(ins, 0, sizeof s);
    ::x = x;
    dfs(s, 0);
    return win[s];
}

int main() {
    freopen("mashiro.in", "r", stdin);
    freopen("mashiro.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> s;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }

    int ans = s;
    int L = s + 1, R = n;
    while(L <= R) {
        int mid = L + R >> 1;
        if(check(mid)) {
            ans = mid;
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }
    cout << ans << "\n";

    return 0;
}