#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;
const int M = 15;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int P = 1e9 + 7;

int n, k;
int w[M], pos[M];
ll v1[M][N], v2[M][N], v[M][N];
int l[M][N], r[M][N], e[M];
int c[N], d[N];
int ans;

void solve() {
    ll res = inf;
    for(int i = 1; i <= k; ++i) {
        res = min(res, v[i][pos[i]]);
    }
    if(res == inf) {
    	cout << -1 << "\n";
    	exit(0);
    }
    ans = (res + ans) % P;
}

inline void dfs(int p){
    if(p == k + 1) {
        solve();
        return;
    }
    for(int i = 1; i <= w[p]; ++i) {
        pos[p] = i;
        dfs(p + 1);
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    cin >> n >> k;
    for(int i = 1; i <= k; ++i) cin >> w[i];
    for(int i = 1; i <= n; ++i) cin >> c[i] >> d[i];
    for(int i = 1; i <= n; ++i) {
        e[c[i]] += d[i];
        for(int j = 1; j <= k; ++j) {
            l[j][i] = min(l[j][i-1], e[j]);
            r[j][i] = min(r[j][i-1], e[j]);
        }
    }
    for(int i = 1; i <= k; ++i) {
        memset(v1[i], 0x3f, sizeof v1[i]);
        memset(v2[i], 0x3f, sizeof v2[i]);
        v1[i][0] = 0;
        v2[i][w[i]+1] = 0;
        int p = 1, curpos = 0;
        for(int j = 1; j <= w[i]; ++j) {
            ++curpos;
            while(1 <= curpos && curpos <= w[i] && p <= n) {
                if(c[p] == i) curpos += d[p];
                ++p;
            }
            if(curpos < 1 || curpos > w[i]) v1[i][j] = p-1;
            else {
                if(e[i] < 0) v1[i][j] = v1[i][j+e[i]] + n;
                else break;
            }
        }
        p = 1, curpos = w[i] + 1;
        for(int j = w[i]; j >= 1; --j) {
            --curpos;
            while(1 <= curpos && curpos <= w[i] && p <= n) {
                if(c[p] == i) curpos += d[p];
                ++p;
            }
            if(curpos < 1 || curpos > w[i]) v2[i][j] = p-1;
            else {
                if(e[i] > 0) v2[i][j] = v2[i][j+e[i]] + n;
                else break;
            }
        }
        for(int j = 1; j <= w[i]; ++j) {
            v[i][j] = min(v1[i][j], v2[i][j]);
        }
    }
    for(int i = 1; i <= k; ++i) sort(v[i] + 1, v[i] + w[i] + 1);
    for(int i = 1; i <= k; ++i) {
    	for(int j = 1; j <= k; ++j) pos[j] = 1;
    	for(int j = 1; j <= w[i]; ++j) {
    		int cnt = 1;
    		for(int jj = 1; jj <= k; ++jj) {
    			if(jj < i) {
    				while(pos[jj] <= w[jj] && v[jj][pos[jj]] <= v[i][j]) ++pos[jj];
    				cnt = 1ll * cnt * (w[jj] - pos[jj] + 1) % P;
    			} else if(jj > i) {
    				while(pos[jj] <= w[jj] && v[jj][pos[jj]] < v[i][j]) ++pos[jj];
    				cnt = 1ll * cnt * (w[jj] - pos[jj] + 1) % P;
    			}
    			if(cnt == 0) break;
    		}
    		if(v[i][j] == inf && cnt) {
    			cout << -1 << "\n";
    			return 0;
    		}
    		ans = (ans + 1ll * v[i][j] % P * cnt) % P;
    	}
    }
    cout << ans << "\n";
    
    return 0;
}
