#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e6 + 5;

int n, m, k;
int a[N], b[N], c[N];

void getf(int l, int r, int pre, int dep, int f[]) {
    if(l == r) {
	f[l] = pre;
	return;
    }
    int mid = l + r >> 1;
    getf(l, mid, pre, dep+1, f);
    rep(i, mid+1, r) {
	int p = i-mid;
	int j = mid-p+1;
	f[i] = f[j] | 1<<dep;
    }
}

void solve(int n, int a[]) {
    int p = 1, pre = 0;
    bool rev = 1;
    rep(i, 0, 20) {
	if(n >> i & 1) {
	    int pre = n >> i+1 << i+1;
	    int l = pre + 1;
	    int r = pre + (1<<i);

	    getf(l, r, pre, 0, a);

	    if(r != n && __builtin_popcount(a[r]^a[r+1]) != 1) reverse(a+l, a+r+1);

	}
    }    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);


    rep(n, 1, (int)1e3) {
	solve(n, a);
	cerr << n << "\n";
    rep(i, 2, n) assert(__builtin_popcount(a[i]^a[i-1]) == 1);
	
    }
    
    return 0;
    
    freopen("ruler.in", "r", stdin);
    freopen("ruler.out", "w", stdout);
    
    cin >> n >> m >> k;
    
    solve(n, a);
    solve(m, b);
    solve(k, c);

    auto getlog = [&](int x) {
		      int res = 0;
		      while(x) ++res, x >>= 1;
		      return res;
		  };
    rep(i, 2, n) assert(__builtin_popcount(a[i]^a[i-1]) == 1);
    rep(i, 2, k) assert(__builtin_popcount(c[i]^c[i-1]) == 1);
    rep(i, 2, m) assert(__builtin_popcount(b[i]^b[i-1]) == 1);

    int x = getlog(m), y = getlog(k);
    rep(i, 1, n) rep(j, 1, m) {
	rep(kk, 1, k) cout << (a[i] << x + y | b[j] << y | c[kk]) << " \n"[kk == k];
    }
    
    return 0;
}

//0 2 3 1 5 4 6
